#include <anixart/ApiPageableRequests.hpp>
#include <anixart/CachingJson.hpp>

namespace anixart {
    using requests::SearchRequest;
    using requests::FilterRequest;
    using namespace json;

    FilterPages::FilterPages(const ApiSession& session, const std::string& token, const int32_t page, const FilterRequest& request, const bool extended_mode) :
        EmptyContentPaginator<Release>(page),
        _session(session),
        _request(request),
        _extended_mode(extended_mode),
        _token(token)
    {}
    CachingJsonObject FilterPages::do_request(const int32_t page) const {
        return _session.api_request(requests::filter::filter(page, _request, _extended_mode, _token));
    }

    StreamingPlatformsPages::StreamingPlatformsPages(const ApiSession& session, const int32_t page, const ReleaseID release_id) :
        Paginator<ReleaseStreamingPlatform>(page),
        _session(session),
        _release_id(release_id)
    {
    }

    CachingJsonObject StreamingPlatformsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::streamingPlatform::release_streaming_platform(static_cast<int64_t>(_release_id)));
    }

    CommentsWeekPages::CommentsWeekPages(const ApiSession& session) :
        Paginator<Comment>(0),
        _session(session)
    {
    }

    CachingJsonObject CommentsWeekPages::do_request(const int32_t page) const {
        return _session.api_request(requests::discover::comments_week());
    }

    DiscussingPages::DiscussingPages(const ApiSession& session, const std::string& token) :
        Paginator<Release>(0),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject DiscussingPages::do_request(const int32_t page) const {
        return _session.api_request(requests::discover::discussing(_token));
    }

    InterestingPages::InterestingPages(const ApiSession& session) :
        Paginator<Interesting>(0),
        _session(session)
    {
    }

    CachingJsonObject InterestingPages::do_request(const int32_t page) const {
        return _session.api_request(requests::discover::intresting());
    }

    RecomendationsPages::RecomendationsPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Release>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject RecomendationsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::discover::recommendations(page, 0, _token));
    }

    WatchingPages::WatchingPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Release>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject WatchingPages::do_request(const int32_t page) const {
        return _session.api_request(requests::discover::watching(page, _token));
    }

    CollectionSearchPages::CollectionSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const SearchRequest& request) :
        Paginator<Collection>(page),
        _session(session),
        _token(token),
        _request(request)
    {
    }

    CachingJsonObject CollectionSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::collection_search(page, _request, _token));
    }

    FavoriteCollectionSearchPages::FavoriteCollectionSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const SearchRequest& request) :
        Paginator<Collection>(page),
        _session(session),
        _token(token),
        _request(request)
    {
    }

    CachingJsonObject FavoriteCollectionSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::favorite_collection_search(page, _request, _token));
    }

    FavoriteSearchPages::FavoriteSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const SearchRequest& request) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _request(request)
    {
    }

    CachingJsonObject FavoriteSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::favorites_search(page, _request, _token));
    }

    HistorySearchPages::HistorySearchPages(const ApiSession& session, const std::string& token, const int32_t page, const SearchRequest& request) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _request(request)
    {
    }

    CachingJsonObject HistorySearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::history_search(page, _request, _token));
    }

    ProfileCollectionSearchPages::ProfileCollectionSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id, const ReleaseID release_id, const SearchRequest& request) :
        Paginator<Collection>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id),
        _release_id(release_id),
        _request(request)
    {
    }

    CachingJsonObject ProfileCollectionSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::profile_collection_search(static_cast<int64_t>(_profile_id), static_cast<int64_t>(_release_id), page, _request, _token));
    }

    ProfileListSearchPages::ProfileListSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const Profile::ListStatus list_status, const SearchRequest& request) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _list_status(list_status),
        _request(request)
    {
    }

    CachingJsonObject ProfileListSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::profile_list_search(static_cast<int32_t>(_list_status), page, _request, _token));
    }

    ProfileSearchPages::ProfileSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const SearchRequest& request) :
        Paginator<Profile>(page),
        _session(session),
        _token(token),
        _request(request)
    {
    }

    CachingJsonObject ProfileSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::profile_search(page, _request, _token));
    }

    ReleaseSearchPages::ReleaseSearchPages(const ApiSession& session, const std::string& token, const int32_t page, const requests::SearchRequest& request) :
        EmptyContentPaginator<Release>(page),
        _session(session),
        _token(token),
        _request(request)
    {
    }

    CachingJsonObject ReleaseSearchPages::do_request(const int32_t page) const {
        return _session.api_request(requests::search::release_search(page, _request, "v2", _token));
    }

    std::vector<Release::Ptr> ReleaseSearchPages::parse_request() {
        CachingJsonObject resp = do_request(_current_page);
        assert_status_code<PageableError>(resp);
        std::vector<ValueType> out = resp.get<CachingJsonArray>("releases").to_vector<ValueType>();
        _is_end = out.empty();
        return out;
    }

    LoginChangeHistoryPages::LoginChangeHistoryPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id) :
        Paginator<LoginChange>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id)
    {
    }

    CachingJsonObject LoginChangeHistoryPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::change_login_history(static_cast<int64_t>(_profile_id), page, _token));
    }

    BlockListPages::BlockListPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Profile>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject BlockListPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::blockList::block_list(page, _token));
    }

    FriendsPages::FriendsPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id) :
        EmptyContentPaginator<Profile>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id)
    {
    }

    CachingJsonObject FriendsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::friends::friends(static_cast<int64_t>(_profile_id), page, _token));
    }

    FriendRequestsInPages::FriendRequestsInPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Profile>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject FriendRequestsInPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::friends::requests_in(page, _token));
    }

    FriendRequestsOutPages::FriendRequestsOutPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Profile>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject FriendRequestsOutPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::friends::requests_out(page, _token));
    }

    ProfileListPages::ProfileListPages(const ApiSession& session, const std::string& token, const int32_t page, const Profile::ListStatus status, const Profile::ListSort sort) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _tab(status),
        _sort(sort)
    {
    }

    CachingJsonObject ProfileListPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::list::profile_list(static_cast<int32_t>(_tab), page, static_cast<int32_t>(_sort), _token));
    }

    ProfileListByProfilePages::ProfileListByProfilePages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id, const Profile::ListStatus status, const Profile::ListSort sort) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id),
        _tab(status),
        _sort(sort)
    {
    }

    ProfileFavoriteReleasesPages::ProfileFavoriteReleasesPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id, const Profile::ListSort sort, const int32_t filter_announce) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id),
        _sort(sort),
        _filter_announce(filter_announce)
    {
    }

    json::CachingJsonObject ProfileFavoriteReleasesPages::do_request(const int32_t page) const {
        return _session.api_request(requests::favorite::favorites(page, static_cast<int32_t>(_sort), static_cast<int32_t>(_filter_announce), _token));
    }

    CachingJsonObject ProfileListByProfilePages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::list::profile_list_by_profile(static_cast<int64_t>(_profile_id), static_cast<int32_t>(_tab), page, static_cast<int32_t>(_sort), _token));
    }

    AllReleaseUnvotedPages::AllReleaseUnvotedPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Release>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject AllReleaseUnvotedPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::releaseVote::all_release_unvoted(page, _token));
    }

    AllReleaseVotedPages::AllReleaseVotedPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id, const Release::ByVoteSort sort) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id),
        _sort(sort)
    {
    }

    CachingJsonObject AllReleaseVotedPages::do_request(const int32_t page) const {
        return _session.api_request(requests::profile::releaseVote::all_release_voted(static_cast<int64_t>(_profile_id), page, static_cast<int32_t>(_sort), _token));
    }

    ReleaseCommentsPages::ReleaseCommentsPages(const ApiSession& session, const std::string& token, const int32_t page, const ReleaseID release_id, const Comment::FilterBy filter_by) :
        Paginator<Comment>(page),
        _session(session),
        _token(token),
        _release_id(release_id),
        _sort(filter_by)
    {
    }

    CachingJsonObject ReleaseCommentsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::comment::comments(static_cast<int64_t>(_release_id), page, static_cast<int32_t>(_sort), _token));
    }

    ProfileReleaseCommentsPages::ProfileReleaseCommentsPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id, const Comment::Sort sort) :
        Paginator<Comment>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id),
        _sort(sort)
    {
    }

    CachingJsonObject ProfileReleaseCommentsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::comment::profile_comments(static_cast<int64_t>(_profile_id), page, static_cast<int32_t>(_sort), _token));
    }

    ReleaseCommentRepliesPages::ReleaseCommentRepliesPages(const ApiSession& session, const std::string& token, const int32_t page, const CommentID comment_id, const Comment::Sort sort) :
        Paginator<Comment>(page),
        _session(session),
        _token(token),
        _comment_id(comment_id),
        _sort(sort)
    {
    }

    CachingJsonObject ReleaseCommentRepliesPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::comment::replies(static_cast<int64_t>(_comment_id), page, static_cast<int32_t>(_sort), _token));
    }

    ReleaseVideoCategoryPages::ReleaseVideoCategoryPages(const ApiSession& session, const int32_t page, const ReleaseID release_id, const ReleaseVideoCategoryID category_id) :
        Paginator<ReleaseVideoCategory>(page),
        _session(session),
        _release_id(release_id),
        _category_id(category_id)
    {
    }

    CachingJsonObject ReleaseVideoCategoryPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::video::category(static_cast<int64_t>(_release_id), _category_id, page));
    }

    ProfileReleaseVideoPages::ProfileReleaseVideoPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id) :
        Paginator<ReleaseVideo>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id)
    {
    }

    CachingJsonObject ProfileReleaseVideoPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::video::profile_video(static_cast<int64_t>(_profile_id), page, _token));
    }

    ReleaseVideoPages::ReleaseVideoPages(const ApiSession& session, const int32_t page, const ReleaseID release_id) :
        Paginator<ReleaseVideo>(page),
        _session(session),
        _release_id(release_id)
    {
    }

    CachingJsonObject ReleaseVideoPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::video::video(static_cast<int64_t>(_release_id), page));
    }

    ReleaseVideoAppealPages::ReleaseVideoAppealPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<ReleaseVideo>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject ReleaseVideoAppealPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::video::appeal::appeals(page, _token));
    }

    ProfileReleaseVideoFavoritesPages::ProfileReleaseVideoFavoritesPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id) :
        Paginator<ReleaseVideo>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id)
    {
    }

    CachingJsonObject ProfileReleaseVideoFavoritesPages::do_request(const int32_t page) const {
        return _session.api_request(requests::release::video::favorite::favorites(static_cast<int64_t>(_profile_id), page, _token));
    }

    HistoryPages::HistoryPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Release>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject HistoryPages::do_request(const int32_t page) const {
        return _session.api_request(requests::history::history(page, _token));
    }

    CollectionsPages::CollectionsPages(const ApiSession& session, const std::string& token, const int32_t page, const int32_t where, const Collection::Sort sort) :
        Paginator<Collection>(page),
        _session(session),
        _token(token),
        _where(where),
        _sort(sort)
    {
    }

    CachingJsonObject CollectionsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::collections(page, _current_page, _where, static_cast<int32_t>(_sort), _token));
    }

    ProfileCollectionsPages::ProfileCollectionsPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id) :
        Paginator<Collection>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id)
    {
    }

    CachingJsonObject ProfileCollectionsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::profile_collections(static_cast<int64_t>(_profile_id), page, _token));
    }

    ReleaseCollectionsPages::ReleaseCollectionsPages(const ApiSession& session, const std::string& token, const int32_t page, const ReleaseID release_id, const Collection::Sort sort) :
        Paginator<Collection>(page),
        _session(session),
        _token(token),
        _release_id(release_id),
        _sort(sort)
    {
    }

    CachingJsonObject ReleaseCollectionsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::release_collections(static_cast<int64_t>(_release_id), page, static_cast<int32_t>(_sort), _token));
    }

    CollectionReleasesPages::CollectionReleasesPages(const ApiSession& session, const std::string& token, const int32_t page, const CollectionID collection_id) :
        Paginator<Release>(page),
        _session(session),
        _token(token),
        _collection_id(collection_id)
    {
    }

    CachingJsonObject CollectionReleasesPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::releases(static_cast<int64_t>(_collection_id), page, _token));
    }

    CollectionCommentsPages::CollectionCommentsPages(const ApiSession& session, const std::string& token, const int32_t page, const CollectionID collection_id, const Comment::Sort sort) :
        Paginator<Comment>(page),
        _session(session),
        _token(token),
        _collection_id(collection_id),
        _sort(sort)
    {
    }

    CachingJsonObject CollectionCommentsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::comment::comments(static_cast<int64_t>(_collection_id), page, static_cast<int32_t>(_sort), _token));
    }

    ProfileCollectionCommentsPages::ProfileCollectionCommentsPages(const ApiSession& session, const std::string& token, const int32_t page, const ProfileID profile_id, const Comment::Sort sort) :
        Paginator<Comment>(page),
        _session(session),
        _token(token),
        _profile_id(profile_id),
        _sort(sort)
    {
    }

    CachingJsonObject ProfileCollectionCommentsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::comment::profile_comments(static_cast<int64_t>(_profile_id), page, static_cast<int32_t>(_sort), _token));
    }

    CollectionCommentRepliesPages::CollectionCommentRepliesPages(const ApiSession& session, const std::string& token, const int32_t page, const CommentID comment_id, const Comment::Sort sort) :
        Paginator<Comment>(page),
        _session(session),
        _token(token),
        _comment_id(comment_id),
        _sort(sort)
    {
    }

    CachingJsonObject CollectionCommentRepliesPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::comment::replies(static_cast<int64_t>(_comment_id), page, static_cast<int32_t>(_sort), _token));
    }

    FavoriteCollectionsPages::FavoriteCollectionsPages(const ApiSession& session, const std::string& token, const int32_t page) :
        Paginator<Collection>(page),
        _session(session),
        _token(token)
    {
    }

    CachingJsonObject FavoriteCollectionsPages::do_request(const int32_t page) const {
        return _session.api_request(requests::collection::favorite::favorites(page, _token));
    }
};