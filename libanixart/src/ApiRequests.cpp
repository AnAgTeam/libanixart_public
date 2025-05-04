#include <anixart/ApiRequests.hpp>
#include <netsess/StringTools.hpp>

namespace anixart::requests {
    constexpr std::string_view base_url = "https://api.anixart.tv/";
    constexpr std::string_view base_url_alt = "https://api-s2.anixart.tv/";

    using network::StringTools;
    using network::UrlParameters;
    using network::KeyValue;

    namespace auth {
        // Definition in ApiRequetsAuth.cpp
    };
    namespace collection {
        ApiGetRequest collection(const int64_t collection_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest collections(const int32_t page, const int32_t previous_page, const int32_t where, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/all/%ld", page),
                .params = UrlParameters({
                    KeyValue("previous_page", std::to_string(previous_page)),
                    KeyValue("where", std::to_string(where)),
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest profile_collections(const int64_t profile_id, const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/all/profile/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest release_collections(const int64_t release_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/all/release/%lld/%ld", release_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest releases(const int64_t collection_id, const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/%lld/releases/%ld", collection_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiPostRequest report(const int64_t collection_id, const CollectionReportRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collection/report/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
    };
    namespace collection::comment {
        ApiPostRequest add(const int64_t collection_id, const CommentAddRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collection/comment/add/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest comment(const int64_t comment_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/comment/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest comments(const int64_t collection_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/comment/all/%lld/%ld", collection_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest remove(const int64_t comment_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/comment/delete/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest edit(const int64_t comment_id, const CommentEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collection/comment/edit/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest process(const int64_t comment_id, const CommentProcessRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collection/comment/process/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest profile_comments(const int64_t profile_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/comment/all/profile/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest replies(const int64_t comment_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collection/comment/replies/%lld/%ld", comment_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
        ApiPostRequest report(const int64_t comment_id, const CommentReportRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collection/comment/report/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest vote(const int64_t comment_id, const int32_t vote, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collection/comment/vote/%lld/%ld", comment_id, vote),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace collection::favorite {
        ApiGetRequest add(const int64_t collection_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collectionFavorite/add/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest remove(const int64_t collection_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collectionFavorite/delete/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest favorites(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collectionFavorite/all/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace collection::my {
        ApiPostRequest create(const CreateEditCollectionRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "collectionMy/create",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest remove(const int64_t collection_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collectionMy/delete/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest edit(const int64_t collection_id, const CreateEditCollectionRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("collectionMy/edit/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostMultipartRequest edit_image(const int64_t collection_id, const network::MultipartPart& image, const std::string& token) {
            return ApiPostMultipartRequest{
                .sub_url = StringTools::snformat("collectionMy/editImage/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .forms = network::MultipartForms({
                    image,
                    new network::MultipartContentPart("name", "image", "text/plain")
                })
            };
        }
        ApiGetRequest release_add(const int64_t collection_id, const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collectionMy/release/add/%lld", collection_id),
                .params = UrlParameters({
                    KeyValue("release_id", std::to_string(release_id)),
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest releases(const int64_t collection_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("collectionMy/%lld/releases", collection_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace profile {
        ApiGetRequest change_login_history(const int64_t profile_id, const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/login/history/all/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest process(const int64_t profile_id, const ProfileProcessRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("profile/process/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest profile(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest social(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/social/%ld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace profile::blockList {
        ApiGetRequest add_to_block_list(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/blocklist/add/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest block_list(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/social/all/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest remove_from_block_list(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/blocklist/remove/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace profile::friends {
        ApiGetRequest friends(const int64_t profile_id, const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/friend/all/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest recommendations(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/friend/recommendations",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest request_hide(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/friend/request/hide/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest request_remove(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/friend/request/remove/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest request_send(const int64_t profile_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/friend/request/send/%lld", profile_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest requests_in(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/friend/requests/in/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest requests_in_last(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/friend/requests/in/last",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest requests_out(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/friend/requests/out/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest requests_out_last(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/friend/requests/out/last",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace profile::list {
        ApiGetRequest add(const int32_t status, const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/list/add/%ld/%lld", status, release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest remove(const int32_t status, const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/list/delete/%ld/%lld", status, release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest profile_list(const int32_t status, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/list/all/%ld/%ld", status, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest profile_list_by_profile(const int64_t profile_id, const int32_t status, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/list/all/%lld/%ld/%ld", profile_id, status, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace profile::preferences {
        ApiPostMultipartRequest avatar_edit(const network::MultipartPart& image, const std::string& token) {
            return ApiPostMultipartRequest{
                .sub_url = "profile/preference/avatar/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .forms = network::MultipartForms({
                    image,
                    new network::MultipartContentPart("name", "image", "text/plain")
                })
            };
        }
        ApiGetRequest change_email(const std::string& current_password, const std::string& current_email, const std::string& new_email, const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/preference/email/change",
                .params = UrlParameters({
                    KeyValue("current_password", current_password),
                    KeyValue("current", current_email),
                    KeyValue("new", new_email),
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest change_email_confirm(const std::string& current_password, const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/preference/email/change/confirm",
                .params = UrlParameters({
                    KeyValue("current", current_password),
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest change_login(const std::string& login, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/login/change",
                .params = UrlParameters({
                    KeyValue("login", login),
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
        ApiPostRequest change_login_info(const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/login/info",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
        ApiGetRequest change_password(const std::string& current_password, const std::string& new_password, const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/preference/password/change",
                .params = UrlParameters({
                    KeyValue("current", current_password),
                    KeyValue("new", new_password),
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest google_bind(const std::string& google_id_token, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/google/bind",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = StringTools::sformat("idToken=%s", google_id_token),
                .type = "application/x-www-form-urlencoded"
            };
        }
        ApiPostRequest google_unbind(const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/google/unbind",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
        ApiGetRequest my(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/preference/my",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest privacy_counts_edit(const PrivacyEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/privacy/counts/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest privacy_friend_request_edit(const PrivacyEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/privacy/friendRequests/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest privacy_social_edit(const PrivacyEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/privacy/social/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest privacy_stats_edit(const PrivacyEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/privacy/stats/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest social(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/preference/social",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest social_pages_edit(const SocialPagesEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/social/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest status_remove(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "profile/preference/status/delete",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest status_edit(const StatusEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/status/edit",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest vk_bind(const std::string& vk_access_token, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/vk/bind",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = StringTools::sformat("accessToken=%s", vk_access_token),
                .type = "application/x-www-form-urlencoded"
            };
        }
        ApiPostRequest vk_unbind(const std::string& token) {
            return ApiPostRequest{
                .sub_url = "profile/preference/vk/unbind",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
    };
    namespace profile::releaseVote {
        ApiGetRequest all_release_unvoted(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("profile/vote/release/unvoted/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest all_release_voted(const int64_t profile_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("/profile/vote/release/voted/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest last_release_unvoted(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "/profile/vote/release/unvoted/last",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
    };
    namespace commentVotes {

    };
    namespace config {

    };
    namespace directLink {
        ApiPostRequest links(const DirectLinkRequest& request) {
            return ApiPostRequest{
                .sub_url = "video/parse",
                .data = request.serialize(),
                .type = "application/json"
            };
        }
    };
    namespace discover {
        ApiPostRequest comments_week() {
            return ApiPostRequest{
                .sub_url = "discover/comments",
                .data = "",
                .type = "application/json"
            };
        }
        ApiPostRequest discussing(const std::string& token) {
            return ApiPostRequest{
                .sub_url = "discover/discussing",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
        ApiPostRequest intresting() {
            return ApiPostRequest{
                .sub_url = "discover/interesting",
                .data = "",
                .type = "application/json"
            };
        }
        ApiPostRequest recommendations(const int32_t page, const int32_t previous_page, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("discover/recommendations/%ld", page),
                .params = UrlParameters({
                    KeyValue("previous_page", std::to_string(previous_page)),
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
        ApiPostRequest watching(const int32_t page, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("discover/watching/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
    };
    namespace episode {
        ApiGetRequest episode_target(int64_t release_id, int64_t source_id, int32_t position) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("episode/target/%lld/%lld/%ld", release_id, source_id, position),
            };
        }
        ApiGetRequest episodes(const int64_t release_id, const int64_t type_id, const int64_t source_id, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("episode/%lld/%lld/%lld", release_id, type_id, source_id),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                })
            };
        }
        ApiPostRequest report(const int64_t release_id, const int64_t source_id, const int32_t position, const EpisodeReportRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("episode/report/%lld/%lld/%ld", release_id, source_id, position),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest sources(const int64_t release_id, const int64_t type_id) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("episode/%lld/%lld", release_id, type_id),
            };
        }
        ApiGetRequest types(const int64_t release_id) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("episode/%lld", release_id),
            };
        }
        ApiPostRequest unwatch(const int64_t release_id, const int64_t source_id, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("episode/unwatch/%lld/%lld", release_id, source_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
        ApiPostRequest unwatch(const int64_t release_id, const int64_t source_id, const int32_t position, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("episode/unwatch/%lld/%lld/%ld", release_id, source_id, position),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
        ApiGetRequest updates(const int64_t release_id, const int32_t page) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("episode/updates/%lld/%ld", release_id, page),
            };
        }
        ApiPostRequest watch(const int64_t release_id, const int64_t source_id, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("episode/watch/%lld/%lld", release_id, source_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
        ApiPostRequest watch(const int64_t release_id, const int64_t source_id, const int32_t position, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("episode/watch/%lld/%lld/%ld", release_id, source_id, position),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "",
                .type = "application/json"
            };
        }
    };
    namespace imporing {

    };
    namespace exporting {

    };
    namespace favorite {
        extern ApiGetRequest add(const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("favorite/add/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        extern ApiGetRequest remove(const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("favorite/delete/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        extern ApiGetRequest favorites(const int32_t page, const int32_t sort, int32_t filter_announce, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("favorite/all/%ld", page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("filter_announce", std::to_string(filter_announce)),
                    KeyValue("token", token)
                })
            };
        }
    };
    namespace filter {
        ApiPostRequest filter(const int32_t page, const FilterRequest& request, const bool extended_mode, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("filter/%ld", page),
                .params = UrlParameters({
                    KeyValue("extended_mode", extended_mode ? "true" : "false"),
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
    };
    namespace history {
        ApiGetRequest add(const int64_t release_id, const int64_t source_id, const int32_t position, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("history/add/%lld/%lld/%ld", release_id, source_id, position),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest remove(const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("history/delete/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest history(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("history/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
    };
    namespace release {
        ApiGetRequest delete_vote(const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/vote/delete/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest random(const bool extended_mode, const std::string& token) {
            return ApiGetRequest{
                .sub_url = "release/random",
                .params = UrlParameters({
                    KeyValue("token", token),
                    KeyValue("extended_mode", extended_mode ? "true" : "false")
                })
            };
        }
        /* random from collection */
        ApiGetRequest random_collection(const int64_t release_id, const bool extended_mode, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/collection/%lld/random", release_id),
                .params = UrlParameters({
                    KeyValue("token", token),
                    KeyValue("extended_mode", extended_mode ? "true" : "false")
                })
            };
        }
        ApiGetRequest random_favorite(const bool extended_mode, const std::string& token) {
            return ApiGetRequest{
                .sub_url = "release/random/favorite",
                .params = UrlParameters({
                    KeyValue("token", token),
                    KeyValue("extended_mode", extended_mode ? "true" : "false")
                })
            };
        }
        ApiGetRequest random_profile_list(const int64_t profile_id, const int32_t status, const bool extended_mode, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/random/profile/list/%lld/%ld", profile_id, status),
                .params = UrlParameters({
                    KeyValue("token", token),
                    KeyValue("extended_mode", extended_mode ? "true" : "false")
                })
            };
        }
        ApiGetRequest release(const int64_t release_id, const bool extended_mode, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token),
                    KeyValue("extended_mode", extended_mode ? "true" : "false")
                })
            };
        }
        ApiPostRequest report(const int64_t release_id, const ReleaseReportRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("release/report/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest vote(const int64_t release_id, const int32_t vote, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/vote/add/%lld/%ld", release_id, vote),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
    };
    namespace release::comment {
        ApiPostRequest add(const int64_t release_id, const CommentAddRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("release/comment/add/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest comment(const int64_t comment_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/comment/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest comments(const int64_t release_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/comment/all/%lld/%ld", release_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest remove(const int64_t comment_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/comment/delete/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiPostRequest edit(const int64_t comment_id, const CommentEditRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("release/comment/edit/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest process(const int64_t comment_id, const CommentProcessRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("release/comment/process/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest profile_comments(const int64_t profile_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/comment/all/profile/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                })
            };
        }
        ApiPostRequest replies(const int64_t comment_id, const int32_t page, const int32_t sort, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("release/comment/replies/%lld/%ld", comment_id, page),
                .params = UrlParameters({
                    KeyValue("sort", std::to_string(sort)),
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
        ApiPostRequest report(const int64_t comment_id, const CommentReportRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("release/comment/report/%lld", comment_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest vote(const int64_t comment_id, const int32_t vote, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/comment/vote/%lld/%ld", comment_id, vote),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
    };
    namespace release::streamingPlatform {
        ApiGetRequest release_streaming_platform(const int64_t release_id) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("release/streaming/platform/%lld", release_id)
            };
        }
    };
    namespace release::video {
        ApiGetRequest categories() {
            return ApiGetRequest{
                .sub_url = "video/release/categories"
            };
        }
        ApiGetRequest category(const int64_t release_id, const int64_t category_id, const int32_t page) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("video/release/%lld/category/%lld/%ld", release_id, category_id, page)
            };
        }
        ApiGetRequest main(const int64_t release_id) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("video/release/%lld", release_id)
            };
        }
        ApiGetRequest profile_video(const int64_t profile_id, const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("video/profile/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest video(const int64_t release_id, const int32_t page) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("video/release/%lld/%ld", release_id, page)
            };
        }
    };
    namespace release::video::appeal {
        ApiPostRequest add(const ReleaseVideoAppealRequest& request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = "video/appeal/add",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = request.serialize(),
                .type = "application/json"
            };
        }
        ApiGetRequest appeals(const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("video/appeal/profile/%lld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiGetRequest appeals(const std::string& token) {
            return ApiGetRequest{
                .sub_url = "video/appeal/profile/last",
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
            };
        }
        ApiPostRequest remove(const int64_t appeal_id, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("video/appeal/delete/%lld", appeal_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = "{}",
                .type = "application/json"
            };
        }
    };
    namespace release::video::favorite {
        ApiGetRequest add(const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("releaseVideoFavorite/add/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest remove(const int64_t release_id, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("releaseVideoFavorite/delete/%lld", release_id),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
        ApiGetRequest favorites(const int64_t profile_id, const int32_t page, const std::string& token) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("releaseVideoFavorite/all/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                })
            };
        }
    };
    namespace search {
        ApiPostRequest collection_search(const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/collections/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest favorite_collection_search(const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/favoriteCollections/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest favorites_search(const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/favorites/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest history_search(const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/history/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest profile_collection_search(const int64_t profile_id, const int64_t release_id, const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/profileCollections/%lld/%ld", profile_id, page),
                .params = UrlParameters({
                    KeyValue("token", token),
                    KeyValue("release_id", std::to_string(release_id))
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest profile_list_search(const int32_t status, const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/profile/list/%ld/%ld", status, page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest profile_search(const int32_t page, const SearchRequest& search_request, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/profiles/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
        ApiPostRequest release_search(const int32_t page, const SearchRequest& search_request, const std::string& api_version, const std::string& token) {
            return ApiPostRequest{
                .sub_url = StringTools::snformat("search/releases/%ld", page),
                .params = UrlParameters({
                    KeyValue("token", token)
                }),
                .headers = {
                    StringTools::sformat("API-Version: %s", api_version)
                },
                .data = search_request.serialize(),
                .type = "application/json"
            };
        }
    };
    namespace type {
        ApiGetRequest types(const int64_t release_id) {
            return ApiGetRequest{
                .sub_url = StringTools::snformat("type/%lld", release_id)
            };
        }
        ApiGetRequest types(const std::string& token) {
            return ApiGetRequest{
                 .sub_url = "type/all",
                 .params = UrlParameters({
                    KeyValue("token", token)
                 })
            };
        }
    };
};
namespace anixart::requests::beta {
    namespace achievements {
        ApiGetRequest get_achievement(const int64_t achievement_id, const std::string& token) {
            return ApiGetRequest{
                 .sub_url = StringTools::snformat("achievement/get/%lld", achievement_id),
                 .params = UrlParameters({
                    KeyValue("token", token)
                 })
            };
        }
    };
    namespace profile::badge {
        ApiGetRequest edit(const int64_t badge_id, const std::string& token) {
            return ApiGetRequest{
                 .sub_url = StringTools::snformat("profile/preference/badge/edit/%lld", badge_id),
                 .params = UrlParameters({
                    KeyValue("token", token)
                 })
            };
        }
    };
};