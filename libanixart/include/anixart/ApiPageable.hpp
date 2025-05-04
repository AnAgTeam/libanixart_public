#pragma once
#include <anixart/ApiErrors.hpp>
#include <anixart/CachingJson.hpp>
#include <netsess/NetTypes.hpp>
#include <netsess/JsonTools.hpp>

#include <list>
#include <functional>
#include <cassert>

namespace anixart {
	template<typename T>
	class Pageable {
	public:
		using ValueType = std::shared_ptr<T>;
		using Ptr = std::shared_ptr<Pageable<T>>;
		using UPtr = std::unique_ptr<Pageable<T>>;

		virtual std::vector<ValueType> next() = 0;
		virtual std::vector<ValueType> prev() = 0;
		virtual std::vector<ValueType> go(const int32_t page) = 0;
		virtual std::vector<ValueType> get() = 0;

		virtual int32_t get_current_page() const = 0;
		virtual bool is_end() const = 0;
		virtual int64_t get_total_count() const = 0;

	protected:
		virtual std::vector<ValueType> parse_request() = 0;
	};

	template<typename T>
	class Paginator : public Pageable<T> {
	public:
		using typename Pageable<T>::ValueType;
		/*
			Lazy initializes. is_end() always returns true until get(), next(), prev() or go() called once, then is_end() returns truly ended state
			Should call get() after initialization
		*/
		Paginator(const int32_t page) :
			_previous_page(page),
			_current_page(page),
			_total_page_count(-1),
			_total_count(-1)
		{}

		std::vector<ValueType> next() override {
			assert(_total_page_count >= 0);
			_previous_page = _current_page;
			if (_current_page >= _total_page_count) {
				_current_page = 0;
			}
			else {
				++_current_page;
			}
			return parse_request();
		}
		std::vector<ValueType> prev() override {
			assert(_total_page_count >= 0);
			_previous_page = _current_page;
			if (_current_page <= 0) {
				_current_page = _total_page_count;
			}
			else {
				--_current_page;
			}
			return parse_request();
		}
		std::vector<ValueType> go(const int32_t page) override {
			assert(_total_page_count >= 0);
			if (page < 0 || page > _total_page_count) {
				return {};
			}
			_previous_page = _current_page;
			_current_page = page;
			return parse_request();
		}
		std::vector<ValueType> get() override {
			return parse_request();
		}

		int32_t get_current_page() const override {
			return _current_page;
		}
		bool is_end() const override {
			return _current_page >= _total_page_count;
		}

		int64_t get_total_count() const override {
			return _total_count;
		}

	protected:
		virtual json::CachingJsonObject do_request(const int32_t page) const = 0;

		std::vector<ValueType> parse_request() override {
			json::CachingJsonObject resp(this->do_request(_current_page));
			assert_status_code<PageableError>(resp);
			_current_page = resp.get<int32_t>("current_page");
			_total_page_count = resp.get<int32_t>("total_page_count");
			_total_count = resp.get<int64_t>("total_count");

			return resp.get<json::CachingJsonArray>("content").to_vector<ValueType>();
		}

		int32_t _previous_page;
		int32_t _current_page;
		int32_t _total_page_count;
		int64_t _total_count;
	};

	template<typename T>
	class EmptyContentPaginator : public Pageable<T> {
	public:
		using typename Pageable<T>::ValueType;

		EmptyContentPaginator(const int32_t page) :
			_current_page(page),
			_previous_page(-1),
			_is_end(true)
		{
		}

		std::vector<ValueType> next() override {
			assert(_previous_page >= 0);
			_previous_page = _current_page;
			if (_is_end) {
				_current_page = 0;
			}
			else {
				++_current_page;
			}
			return parse_request();
		}
		std::vector<ValueType> prev() override {
			assert(_previous_page >= 0);
			_previous_page = _current_page;
			if (_current_page > 0) {
				--_current_page;
			}
			return parse_request();
		}
		std::vector<ValueType> go(const int32_t page) override {
			assert(_previous_page >= 0);
			if (page < 0) {
				return {};
			}
			_previous_page = _current_page;
			_current_page = page;
			return parse_request();
		}
		std::vector<ValueType> get() override {
			_previous_page = _current_page;
			return parse_request();
		}

		int32_t get_current_page() const override {
			return _current_page;
		}

		bool is_end() const override {
			return _is_end;
		}

		int64_t get_total_count() const override {
			return _total_count;
		}

	protected:
		virtual json::CachingJsonObject do_request(const int32_t page) const = 0;

		std::vector<ValueType> parse_request() override {
			json::CachingJsonObject resp = do_request(_current_page);
			assert_status_code<PageableError>(resp);
			_total_count = resp.get<int64_t>("total_count");

			std::vector<ValueType> out = resp.get<json::CachingJsonArray>("content").to_vector<ValueType>();
			_is_end = out.empty();
			return out;
		}

		int32_t _previous_page;
		int32_t _current_page;
		int64_t _total_count;
		bool _is_end;
	};
};

