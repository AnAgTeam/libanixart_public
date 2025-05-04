#pragma once
#include <anixart/ApiRequestTypes.hpp>
#include <anixart/ApiRequestsAuth.hpp>
#include <netsess/UrlSession.hpp>

#include <string>
#include <string_view>

//#define LIBANIXART_AUTH_PRESENTED

namespace anixart {
	class ApiGetRequest {
	public:
		std::string sub_url;
		network::UrlParameters params = network::UrlParameters();
		std::vector<std::string> headers = {};
	};
	class ApiPostRequest {
	public:
		std::string sub_url;
		network::UrlParameters params = network::UrlParameters();
		std::vector<std::string> headers = {};
		std::string data;
		std::string_view type;
	};
	class ApiPostMultipartRequest {
	public:
		std::string sub_url;
		network::UrlParameters params = network::UrlParameters();
		std::vector<std::string> headers = {};
		network::MultipartForms forms;
	};

	namespace requests {
		extern const std::string_view base_url;
		extern const std::string_view base_url_alt;

#ifdef LIBANIXART_AUTH_PRESENTED
		// Sources of these functions is declared in ApiRequestsAuth.cpp
		namespace auth {
			extern ApiPostRequest firebase(const std::string& token);
			extern ApiPostRequest restore(const std::string& email_or_login);
			extern ApiPostRequest restore_resend(const std::string& email_or_login, const std::string& password, const std::string& hash);
			extern ApiPostRequest restore_verify(const std::string& email_or_login, const std::string& password, const std::string& hash, const std::string& code);
			extern ApiPostRequest sign_in(const std::string& login, const std::string& password);
			extern ApiPostRequest sign_in_google(const std::string& google_id_token);
			extern ApiPostRequest sign_in_vk(const std::string& vk_access_token);
			extern ApiPostRequest sign_up(const std::string& login, const std::string& email, const std::string& password);
			extern ApiPostRequest sign_up_google(const std::string& login, const std::string& email, const std::string& google_id_token);
			extern ApiPostRequest sign_up_vk(const std::string& login, const std::string& email, const std::string& vk_access_token);
			struct AuthKeys {
				static constexpr std::string_view password = "password";
				static constexpr std::string_view google = "googleIdToken";
				static constexpr std::string_view vk = "vkAccessToken";
			};
			extern ApiPostRequest resend(const std::string& login, const std::string& email, const std::string& hash, std::string_view auth_key, const std::string& auth_value);
			extern ApiPostRequest verify(const std::string& login, const std::string& email, const std::string& hash, const std::string& code, std::string_view auth_key, const std::string& auth_value);
		};
#endif
		namespace collection {
			extern ApiGetRequest collection(const int64_t collection_id, const std::string& token);
			extern ApiGetRequest collections(const int32_t page, const int32_t previous_page, const int32_t where, const int32_t sort, const std::string& token);
			extern ApiGetRequest profile_collections(const int64_t profile_id, const int32_t page, const std::string& token);
			extern ApiGetRequest release_collections(const int64_t release_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiGetRequest releases(const int64_t collection_id, const int32_t page, const std::string& token);
			extern ApiPostRequest report(const int64_t collection_id, const CollectionReportRequest& request, const std::string& token);
		};
		namespace collection::comment {
			extern ApiPostRequest add(const int64_t collection_id, const CommentAddRequest& request, const std::string& token);
			extern ApiGetRequest comment(const int64_t comment_id, const std::string& token);
			extern ApiGetRequest comments(const int64_t collection_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiGetRequest remove(const int64_t comment_id, const std::string& token);
			extern ApiPostRequest edit(const int64_t comment_id, const CommentEditRequest& request, const std::string& token);
			extern ApiPostRequest process(const int64_t comment_id, const CommentProcessRequest& request, const std::string& token);
			extern ApiGetRequest profile_comments(const int64_t profile_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiPostRequest replies(const int64_t comment_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiPostRequest report(const int64_t comment_id, const CommentReportRequest& request, const std::string& token);
			extern ApiGetRequest vote(const int64_t comment_id, const int32_t vote, const std::string& token);
		};
		namespace collection::favorite {
			extern ApiGetRequest add(const int64_t collection_id, const std::string& token);
			extern ApiGetRequest remove(const int64_t collection_id, const std::string& token);
			extern ApiGetRequest favorites(const int32_t page, const std::string& token);
		};
		namespace collection::my {
			extern ApiPostRequest create(const CreateEditCollectionRequest& request, const std::string& token);
			extern ApiGetRequest remove(const int64_t collection_id, const std::string& token);
			extern ApiPostRequest edit(const int64_t collection_id, const CreateEditCollectionRequest& request, const std::string& token);
			extern ApiPostMultipartRequest edit_image(const int64_t collection_id, const network::MultipartPart& image, const std::string& token);
			extern ApiGetRequest release_add(const int64_t collection_id, const int64_t release_id, const std::string& token);
			extern ApiGetRequest releases(const int64_t collection_id, const std::string& token);
		};
		namespace profile {
			extern ApiGetRequest change_login_history(const int64_t profile_id, const int32_t page, const std::string& token);
			extern ApiPostRequest process(const int64_t profile_id, const ProfileProcessRequest& request, const std::string& token);
			extern ApiGetRequest profile(const int64_t profile_id, const std::string& token);
			extern ApiGetRequest social(const int64_t profile_id, const std::string& token);
		};
		namespace profile::blockList {
			extern ApiGetRequest add_to_block_list(const int64_t profile_id, const std::string& token);
			extern ApiGetRequest block_list(const int32_t page, const std::string& token);
			extern ApiGetRequest remove_from_block_list(const int64_t profile_id, const std::string& token);
		};
		namespace profile::friends {
			extern ApiGetRequest friends(const int64_t profile_id, const int32_t page, const std::string& token);
			extern ApiGetRequest recommendations(const std::string& token);
			extern ApiGetRequest request_hide(const int64_t profile_id, const std::string& token);
			extern ApiGetRequest request_remove(const int64_t profile_id, const std::string& token);
			extern ApiGetRequest request_send(const int64_t profile_id, const std::string& token);
			extern ApiGetRequest requests_in(const int32_t page, const std::string& token);
			extern ApiGetRequest requests_in_last(const std::string& token);
			extern ApiGetRequest requests_out(const int32_t page, const std::string& token);
			extern ApiGetRequest requests_out_last(const std::string& token);
		};
		namespace profile::list {
			extern ApiGetRequest add(const int32_t status, const int64_t release_id, const std::string& token);
			extern ApiGetRequest remove(const int32_t status, const int64_t release_id, const std::string& token);
			extern ApiGetRequest profile_list(const int32_t status, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiGetRequest profile_list_by_profile(const int64_t profile_id, const int32_t status, const int32_t page, const int32_t sort, const std::string& token);
		};
		namespace profile::preferences {
			extern ApiPostMultipartRequest avatar_edit(const network::MultipartPart& image, const std::string& token);
			extern ApiGetRequest change_email(const std::string& current_password, const std::string& current_email, const std::string& new_email, const std::string& token);
			extern ApiGetRequest change_email_confirm(const std::string& current_password, const std::string& token);
			extern ApiPostRequest change_login(const std::string& login, const std::string& token);
			extern ApiPostRequest change_login_info(const std::string& token);
			extern ApiGetRequest change_password(const std::string& current_password, const std::string& new_password, const std::string& token);
			extern ApiPostRequest google_bind(const std::string& google_id_token, const std::string& token);
			extern ApiPostRequest google_unbind(const std::string& token);
			extern ApiGetRequest my(const std::string& token);
			extern ApiPostRequest privacy_counts_edit(const PrivacyEditRequest& request, const std::string& token);
			extern ApiPostRequest privacy_friend_request_edit(const PrivacyEditRequest& request, const std::string& token);
			extern ApiPostRequest privacy_social_edit(const PrivacyEditRequest& request, const std::string& token);
			extern ApiPostRequest privacy_stats_edit(const PrivacyEditRequest& request, const std::string& token);
			extern ApiGetRequest social(const std::string& token);
			extern ApiPostRequest social_pages_edit(const SocialPagesEditRequest& request, const std::string& token);
			extern ApiGetRequest status_remove(const std::string& token);
			extern ApiPostRequest status_edit(const StatusEditRequest& request, const std::string& token);
			extern ApiPostRequest vk_bind(const std::string& vk_access_token, const std::string& token);
			extern ApiPostRequest vk_unbind(const std::string& token);
		};
		namespace profile::releaseVote {
			extern ApiGetRequest all_release_unvoted(const int32_t page, const std::string& token);
			extern ApiGetRequest all_release_voted(const int64_t profile_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiGetRequest last_release_unvoted(const std::string& token);
		};
		namespace commentVotes {

		};
		namespace config {

		};
		namespace directLink {
			/* deprecated */
			extern ApiPostRequest links(const DirectLinkRequest& request);
		};
		namespace discover {
			extern ApiPostRequest comments_week();
			extern ApiPostRequest discussing(const std::string& token);
			extern ApiPostRequest intresting();
			extern ApiPostRequest recommendations(const int32_t page, const int32_t previous_page, const std::string& token);
			extern ApiPostRequest watching(const int32_t page, const std::string& token);
		};
		namespace episode {
			extern ApiGetRequest episode_target(int64_t release_id, int64_t source_id, int32_t position);
			extern ApiGetRequest episodes(const int64_t release_id, const int64_t type_id, const int64_t source_id, const int32_t sort, const std::string& token);
			extern ApiPostRequest report(const int64_t release_id, const int64_t source_id, const int32_t position, const EpisodeReportRequest& request, const std::string& token);
			extern ApiGetRequest sources(const int64_t release_id, const int64_t type_id);
			extern ApiGetRequest types(const int64_t release_id);
			extern ApiPostRequest unwatch(const int64_t release_id, const int64_t source_id, const std::string& token);
			extern ApiPostRequest unwatch(const int64_t release_id, const int64_t source_id, const int32_t position, const std::string& token);
			extern ApiGetRequest updates(const int64_t release_id, const int32_t page);
			extern ApiPostRequest watch(const int64_t release_id, const int64_t source_id, const std::string& token);
			extern ApiPostRequest watch(const int64_t release_id, const int64_t source_id, const int32_t position, const std::string& token);
		};
		namespace importing {
			
		};
		namespace exporting {

		};
		namespace favorite {
			extern ApiGetRequest add(const int64_t release_id, const std::string& token);
			extern ApiGetRequest remove(const int64_t release_id, const std::string& token);
			extern ApiGetRequest favorites(const int32_t page, const int32_t sort, int32_t filter_announce, const std::string& token);
		};
		namespace filter {
			extern ApiPostRequest filter(const int32_t page, const FilterRequest& request, const bool extended_mode, const std::string& token);
		};
		namespace history {
			extern ApiGetRequest add(const int64_t release_id, const int64_t source_id, const int32_t position, const std::string& token);
			extern ApiGetRequest remove(const int64_t release_id, const std::string& token);
			extern ApiGetRequest history(const int32_t page, const std::string& token);
		};
		namespace release {
			extern ApiGetRequest delete_vote(const int64_t release_id, const std::string& token);
			extern ApiGetRequest random(const bool extended_mode, const std::string& token);
			/* random from collection */
			extern ApiGetRequest random_collection(const int64_t release_id, const bool extended_mode, const std::string& token);
			extern ApiGetRequest random_favorite(const bool extended_mode, const std::string& token);
			extern ApiGetRequest random_profile_list(const int64_t profile_id, const int32_t status, const bool extended_mode, const std::string& token);
			extern ApiGetRequest release(const int64_t release_id, const bool extended_mode, const std::string& token);
			extern ApiPostRequest report(const int64_t release_id, const ReleaseReportRequest& request, const std::string& token);
			extern ApiGetRequest vote(const int64_t release_id, const int32_t vote, const std::string& token);
		};
		namespace release::comment {
			extern ApiPostRequest add(const int64_t release_id, const CommentAddRequest& request, const std::string& token);
			extern ApiGetRequest comment(const int64_t comment_id, const std::string& token);
			extern ApiGetRequest comments(const int64_t release_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiGetRequest remove(const int64_t comment_id, const std::string& token);
			extern ApiPostRequest edit(const int64_t comment_id, const CommentEditRequest& request, const std::string& token);
			extern ApiPostRequest process(const int64_t comment_id, const CommentProcessRequest& request, const std::string& token);
			extern ApiGetRequest profile_comments(const int64_t profile_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiPostRequest replies(const int64_t comment_id, const int32_t page, const int32_t sort, const std::string& token);
			extern ApiPostRequest report(const int64_t comment_id, const CommentReportRequest& request, const std::string& token);
			extern ApiGetRequest vote(const int64_t comment_id, const int32_t vote, const std::string& token);
		};
		namespace release::streamingPlatform {
			extern ApiGetRequest release_streaming_platform(const int64_t release_id);
		};
		namespace release::video {
			extern ApiGetRequest categories();
			extern ApiGetRequest category(const int64_t release_id, const int64_t category_id, const int32_t page);
			extern ApiGetRequest main(const int64_t release_id);
			extern ApiGetRequest profile_video(const int64_t profile_id, const int32_t page, const std::string& token);
			extern ApiGetRequest video(const int64_t release_id, const int32_t page);
		};
		namespace release::video::appeal {
			extern ApiPostRequest add(const ReleaseVideoAppealRequest& request, const std::string& token);
			extern ApiGetRequest appeals(const int32_t page, const std::string& token);
			extern ApiGetRequest appeals(const std::string& token);
			extern ApiPostRequest remove(const int64_t appeal_id, const std::string& token);
		};
		namespace release::video::favorite {
			extern ApiGetRequest add(const int64_t release_id, const std::string& token);
			extern ApiGetRequest remove(const int64_t release_id, const std::string& token);
			extern ApiGetRequest favorites(const int64_t profile_id, const int32_t page, const std::string& token);
		};
		namespace search {
			extern ApiPostRequest collection_search(const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest favorite_collection_search(const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest favorites_search(const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest history_search(const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest profile_collection_search(const int64_t profile_id, const int64_t release_id, const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest profile_list_search(const int32_t status, const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest profile_search(const int32_t page, const SearchRequest& search_request, const std::string& token);
			extern ApiPostRequest release_search(const int32_t page, const SearchRequest& search_request, const std::string& api_version, const std::string& token);
		};
		namespace type {
			extern ApiGetRequest types(const int64_t release_id);
			extern ApiGetRequest types(const std::string& token);
		};
	};
	namespace requests::beta {
		namespace achievements {
			extern ApiGetRequest get_achievement(const int64_t achievement_id, const std::string& token);
		};
		namespace profile::badge {
			extern ApiGetRequest edit(const int64_t badge_id, const std::string& token);
		};
	};
};

