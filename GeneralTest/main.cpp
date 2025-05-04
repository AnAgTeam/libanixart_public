#include <anixart/Api.hpp>
#include <anixart/ApiTypes.hpp>
#include <anixart/ApiErrors.hpp>
#include <anixart/ApiRequests.hpp>
#include <anixart/ApiPageableRequests.hpp>
#include <anixart/Parsers.hpp>
#include <anixart/CachingJson.hpp>
#include <anixart/Version.hpp>

#include <iostream>
#include <sstream>

#include <functional>
#include <chrono>

#include <io.h>
#include <fcntl.h>

#include "Secrets.hpp"

//#define PRINT_ALLOCATION_INFO

#pragma execution_character_set("utf-8")

template<typename T>
size_t bench(std::function<void()> func, size_t count) {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i) {
        func();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<T>(end_time - start_time).count();
    return count / max(delta, 1);
}

using namespace anixart;
using namespace anixart::requests;
using namespace anixart::json;
using namespace anixart::parsers;

static bool print_alloc_info = false;
static size_t print_alloc_info_index = 0;
#if defined(PRINT_ALLOCATION_INFO)
void* operator new(size_t size) {
    if (print_alloc_info) {
        std::cout << print_alloc_info_index++ << ": allocation (" << size << " bytes)" << std::endl;
    }
    return malloc(size);
}
#endif

class FooBase {
public:
    FooBase(int64_t a) : a(a) {}
    virtual ~FooBase() {}
    int64_t a;
};
class Foo : public FooBase {
public:
    Foo(int64_t a, int64_t b) : FooBase(a), b(b) {}
    int64_t b;
};

template<typename TCast, typename TArg>
static std::vector<std::shared_ptr<TCast>> vector_dynamic_pointer_cast(const std::vector<std::shared_ptr<TArg>>& vec) {
    std::vector<std::shared_ptr<TCast>> out_vec;
    out_vec.reserve(vec.size());
    for (auto& item : vec) {
        out_vec.push_back(std::dynamic_pointer_cast<TCast>(item));
    }
    return out_vec;
}

int main() {
    (void)_setmode(_fileno(stdin), _O_WTEXT);
    SetConsoleOutputCP(CP_UTF8);

    //volatile std::string object = InlineJsonExperimental::create_object("key", 1, "value", true);

    network::UrlSession::init();

    //return release_info_tool_main();

    try {
        using namespace std::chrono_literals;
#ifdef LIBANIXART_TEST_TOKEN_SECRET_PRESENTED
        std::string token(test_token_secret);
#else
        std::string token = "";
#endif
        ProfileID my_profile_id(4032884);
        Api api("ru_RU", "libanixart", LIBANIXART_API_VERSION "-1");
        api.set_token(token);
        ApiSession& sess = api.get_session();
        sess.set_verbose(true, false);
        sess.switch_base_url(false);

        Parsers parsers;
        ReleaseID rel_id = static_cast<ReleaseID>(16649);

        //for (int i = 0; i < 100; ++i) {
        //    auto ach_resp = sess.api_request(requests::beta::achievements::get_achievement(i, token));
        //    std::cout << "Code: " << ach_resp["code"] << " (" << i << ")\n";
        //    std::this_thread::sleep_for(2s);
        //}

        auto test_resp = sess.api_request(requests::beta::profile::badge::edit(6, token));

        auto [my_profile, _] = api.profiles().get_profile(my_profile_id);

        //std::vector<std::shared_ptr<FooBase>> bases = {
        //    std::dynamic_pointer_cast<FooBase>(std::make_shared<Foo>(2, 4))
        //};
        //std::vector<std::shared_ptr<Foo>> foos = vector_dynamic_pointer_cast<Foo>(bases);

        //std::vector<Comment::Ptr> release_comments = api.releases().release_comments(rel_id, 0, Comment::FilterBy::All)->get();

        //std::vector<Comment::Ptr> replies = api.releases().replies_to_comment(CommentID(5893767), 0, Comment::Sort::Oldest)->get();
        //for (Comment::Ptr& comment : replies) {
        //    std::cout << "[" << comment->author->username << "] " << comment->message << std::endl;
        //}

        //Comment::Ptr comment = api.releases().release_comment(CommentID(5893767));

        //std::vector<Collection::Ptr> collections = api.collections().all_collections(Collection::Sort::WeekPopular, 1, 0)->get();

        //requests::FilterRequest filter_request;
        //filter_request.genres = { "" };
        //filter_request.sort = requests::FilterRequest::Sort::Grade;
        //std::vector<Release::Ptr> releases = api.search().filter_search(filter_request, false, 0)->get();

        //requests::CommentAddRequest request;
        //request.message = "Lolpojoholou, эщкере тебе";
        //request.parent_comment_id = CommentID(5893767);
        //request.reply_to_profile_id = ProfileID(21948);
        //request.is_spoiler = false;
        //api.releases().add_release_comment(ReleaseID(17632), request);
    
        std::vector<EpisodeType::Ptr> types = api.episodes().get_release_types(rel_id);
        std::vector<EpisodeSource::Ptr> sources = api.episodes().get_release_sources(rel_id, types[0]->id);
        std::vector<Episode::Ptr> episodes = api.episodes().get_release_episodes(rel_id, types[0]->id, sources[0]->id, Episode::Sort::FromLeast);
        Episode::Ptr ep_target = api.episodes().get_episode_target(rel_id, sources[0]->id, episodes[0]->position);

        auto urls = parsers.extract_info(ep_target->url);
        if (urls.empty()) {
            if (parsers.get_parser(ep_target->url) == nullptr) {
                std::cout << "No known parsers for target" << std::endl;
            }
            else {
                std::cout << "Failed to get urls" << std::endl;
            }
        }

        std::cout << "Profile" << std::endl;
    }
    catch (const GenericReleaseError& e) {
        std::cout << e.what() << ". Code: " << e.get_code() << "\n";
    }
    catch (const ApiRequestError& e) {
        std::cout << e.what() << ". Code: " << e.get_code() << "\n";
    }
    catch (const ApiError& e) {
        std::cout << e.what() << std::endl;
    }
    //catch (const JsonError& e) {
    //    std::cout << e.what() << "\n";
    //}

}
