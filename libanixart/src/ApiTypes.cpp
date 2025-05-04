#include <anixart/ApiTypes.hpp>
#include <anixart/CachingJson.hpp>
#include <netsess/JsonTools.hpp>

namespace anixart {
	using namespace json;
	using ParseJson = network::json::ParseJson;

	static int32_t parse_friend_status(CachingJsonValue friend_status_value) {
		if (friend_status_value.is_null()) {
			return -1;
		}
		return friend_status_value.as_int64();
	}

	ProfileToken::ProfileToken(const int64_t id, const std::string& token) :
		id(id),
		token(token)
	{}

	ProfileToken::ProfileToken(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		token(object.get<std::string>("token"))
	{}

	ProfileWatchDynamic::ProfileWatchDynamic(json::CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		day(object.get<std::chrono::day>("day")),
		watched_count(object.get<int32_t>("count")),
		date(object.get<TimestampPoint>("timestamp"))
	{}

	Role::Role(json::CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		name(object.get<std::string>("name")),
		color(object.get<std::string>("color"))
	{}

	Profile::Profile(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		username(object.get<std::string>("login")),
		avatar_url(object.get<std::string>("avatar")),
		status(object.get_if<std::string>("status", ParseJson::not_null)),
		telegram_page(object.get<std::string>("tg_page")),
		vk_page(object.get<std::string>("vk_page")),
		instagram_page(object.get<std::string>("inst_page")),
		discord_page(object.get<std::string>("discord_page")),
		tt_page(object.get<std::string>("tt_page")),
		last_activity_time(object.get<TimestampPoint>("last_activity_time")),
		register_date(object.get<TimestampPoint>("register_date")),

		is_banned(object.get<bool>("is_banned")),
		is_perm_banned(object.get<bool>("is_perm_banned")),
		ban_expires(object.get<TimestampPoint>("ban_expires")),
		ban_reason(object.get_if<std::string>("ban_reason", ParseJson::not_null)),

		privilege_level(object.get<PrivilegeLevel>("privilege_level")),
		watched_count(object.get<int32_t>("completed_count")),
		dropped_count(object.get<int32_t>("dropped_count")),
		watched_time(object.get<int64_t>("watched_time")),
		watching_count(object.get<int32_t>("watching_count")),
		plan_count(object.get<int32_t>("plan_count")),
		hold_on_count(object.get<int32_t>("hold_on_count")),
		favorite_count(object.get<int32_t>("favorite_count")),
		video_count(object.get<int32_t>("video_count")),
		watched_episode_count(object.get<int32_t>("watched_episode_count")),
		comment_count(object.get<int32_t>("comment_count")),
		collection_count(object.get<int32_t>("collection_count")),
		rating_score(object.get<int32_t>("rating_score")),
		friend_status(parse_friend_status(object.get<CachingJsonValue>("friend_status"))),
		friend_count(object.get<int32_t>("friend_count")),
		votes(object.get<CachingJsonArray>("votes").to_vector<Release::Ptr>()),
		history(object.get<CachingJsonArray>("history").to_vector<Release::Ptr>()),
		watch_dynamics(object.get<CachingJsonArray>("watch_dynamics").to_vector<ProfileWatchDynamic::Ptr>()),
		roles(object.get<CachingJsonArray>("roles").to_vector<Role::Ptr>()),

		is_blocked(object.get<bool>("is_blocked")),
		is_me_blocked(object.get<bool>("is_me_blocked")),
		block_added_date(object.get_if<TimestampPoint>("block_added_date", ParseJson::not_null)),

		is_sponsor(object.get<bool>("is_sponsor")),
		sponsorship_expires(object.get<TimestampPoint>("sponsorshipExpires")),

		is_online(object.get<bool>("is_online")),
		is_verified(object.get<bool>("is_verified")),
		is_social(object.get_if<bool>("is_social", ParseJson::exists)),
		is_social_hidden(object.get<bool>("is_social_hidden")),
		is_stats_hidden(object.get<bool>("is_stats_hidden")),
		is_counts_hidden(object.get<bool>("is_counts_hidden")),
		is_comment_notifications_enabled(object.get<bool>("is_comment_notifications_enabled")),
		is_release_type_notifications_enabled(object.get<bool>("is_release_type_notifications_enabled")),
		is_related_release_notifications_enabled(object.get<bool>("is_related_release_notifications_enabled")),
		is_report_process_notifications_enabled(object.get<bool>("is_report_process_notifications_enabled")),
		is_my_collection_comment_notifications_enabled(object.get<bool>("is_my_collection_comment_notifications_enabled")),
		is_my_article_comment_notifications_enabled(object.get<bool>("is_my_article_comment_notifications_enabled")),
		is_episode_notifications_enabled(object.get<bool>("is_episode_notifications_enabled")),
		is_first_episode_notification_enabled(object.get<bool>("is_first_episode_notification_enabled")),
		is_friend_requests_disallowed(object.get<bool>("is_friend_requests_disallowed")),
		is_login_changed(object.get_if<bool>("is_login_changed", ParseJson::exists)),
		is_vk_bound(object.get<bool>("is_vk_bound")),
		is_google_bound(object.get<bool>("is_vk_bound"))
	{}

	Profile::FriendStatus Profile::get_friend_status_to(ProfileID other_id) const {
		if (friend_status == -1) {
			return FriendStatus::NotFriends;
		}
		if (friend_status == 2) {
			return FriendStatus::Friends;
		}
		if ((friend_status == 0 && other_id < id) || (friend_status == 1 && other_id >= id)) {
			return FriendStatus::SendedRequest;
		}
		return (friend_status == 1 && other_id < id) || (friend_status == 0 && other_id >= id) ? FriendStatus::RecievedRequest : FriendStatus::NotFriends;
	}

	ReleaseRelated::ReleaseRelated(json::CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		name(object.get<std::string>("name")),
		name_ru(object.get<std::string>("nameRu")),
		description(object.get_if<std::string>("description", ParseJson::not_null)),
		image_url(object.get<std::string>("image")),
		image_urls(object.get_if<CachingJsonArray>("images", ParseJson::not_null).to_vector<std::string>()),
		release_count(object.get<int64_t>("int64_t"))
	{}

	ReleaseVideoBanner::ReleaseVideoBanner(json::CachingJsonObject& object) :
		action_id(object.get<Action>("action_id")),
		name(object.get<std::string>("name")),
		image_url(object.get<std::string>("image")),
		value(object.get<std::string>("value")),
		is_new(object.get<bool>("is_new"))
	{}

	Comment::Comment(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		parent_comment_id(object.get_if<int64_t>("parent_comment_id", ParseJson::not_null)),
		message(object.get<std::string>("message")),
		vote(object.get<int32_t>("vote")),
		vote_count(object.get<int32_t>("vote_count")),
		reply_count(object.get<int64_t>("reply_count")),
		date(object.get<TimestampPoint>("timestamp")),
		author(object.get<Profile::Ptr>("profile")),
		release(object.get_if<Release::Ptr>("release", ParseJson::exists)),
		collection(object.get_if<Collection::Ptr>("collection", ParseJson::exists)),
		is_deleted(object.get<bool>("is_deleted")),
		is_edited(object.get<bool>("is_edited")),
		is_spoiler(object.get<bool>("is_spoiler"))
	{}

	Release::Release(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		title_original(object.get_if<std::string>("title_original", ParseJson::not_null)),
		title_ru(object.get_if<std::string>("title_ru", ParseJson::not_null)),
		title_alt(object.get_if<std::string>("title_alt", ParseJson::not_null)),
		description(object.get_if<std::string>("description", ParseJson::not_null)),
		author(object.get_if<std::string>("author", ParseJson::not_null)),
		director(object.get_if<std::string>("director", ParseJson::not_null)),
		studio(object.get_if<std::string>("studio", ParseJson::not_null)),
		image_url(object.get_if<std::string>("image", ParseJson::not_null)),
		country(object.get_if<std::string>("country", ParseJson::not_null)),
		translators(object.get_if<std::string>("translators", ParseJson::not_null)),
		year(object.get_if<std::string>("year", ParseJson::not_null)),
		genres(object.get_if<std::string>("genres", ParseJson::not_null)),
		rating(object.get<int32_t>("rating")),
		grade(object.get<double>("grade")),
		status(object.get<CachingJsonObject>("status").get<Status>("id")),
		category(object.get<CachingJsonObject>("category").get<Category>("id")),
		season(object.get<Season>("season")),
		release_date(object.get_if<std::string>("release_date", ParseJson::not_null)),
		creation_date(object.get_if<TimestampPoint>("creation_date", ParseJson::not_null)),
		last_update_date(object.get_if<TimestampPoint>("last_update_date", ParseJson::not_null)),
		screenshot_image_urls(object.get<CachingJsonArray>("screenshot_images").to_vector<std::string>()),
		related_releases(object.get<CachingJsonArray>("related_releases").to_vector<Release::Ptr>()),
		related(object.get<ReleaseRelated::Ptr>("related")),
		video_banners(object.get<CachingJsonArray>("video_banners").to_vector<ReleaseVideoBanner::Ptr>()),
		comments(object.get<CachingJsonArray>("comments").to_vector<Comment::Ptr>()),

		age_rating(object.get<AgeRating>("age_rating")),
		duration(object.get<std::chrono::minutes>("duration")),
		broadcast(object.get<int32_t>("broadcast") - 1),
		aired_on_date(object.get<TimestampPoint>("aired_on_date")),
		profile_release_type_notification_preference_count(object.get_if<int32_t>("profile_release_type_notification_preference_count", ParseJson::exists)),
		// something here,
		vote1_count(object.get_if<int32_t>("vote_1_count", ParseJson::exists)),
		vote2_count(object.get_if<int32_t>("vote_2_count", ParseJson::exists)),
		vote3_count(object.get_if<int32_t>("vote_3_count", ParseJson::exists)),
		vote4_count(object.get_if<int32_t>("vote_4_count", ParseJson::exists)),
		vote5_count(object.get_if<int32_t>("vote_5_count", ParseJson::exists)),
		vote_count(object.get<int32_t>("vote_count")),
		your_vote(object.get_if<int32_t>("your_vote", ParseJson::exists_not_null)),
		voted_date(object.get_if<TimestampPoint>("voted_at", ParseJson::exists)),
		my_vote(object.get_if<int32_t>("my_vote", ParseJson::exists_not_null)),

		episodes_total(object.get_if<int32_t>("episodes_total", ParseJson::not_null)),
		collection_count(object.get_if<int64_t>("collection_count", ParseJson::exists)),
		favorite_count(object.get<int32_t>("favorites_count")),
		comment_count(object.get_if<int64_t>("comment_count", ParseJson::exists)),
		comment_per_day_count(object.get_if<int32_t>("comment_per_day_count", ParseJson::exists)),
		watched_count(object.get_if<int32_t>("completed_count", ParseJson::exists)),
		dropped_count(object.get_if<int32_t>("dropped_count", ParseJson::exists)),
		hold_on_count(object.get_if<int32_t>("hold_on_count", ParseJson::exists)),
		plan_count(object.get_if<int32_t>("plan_count", ParseJson::exists)),
		watching_count(object.get_if<int32_t>("watching_count", ParseJson::exists)),

		episode_last_update(object.get_if<EpisodeUpdate::Ptr>("episode_last_update", ParseJson::not_null)),
		episodes_released(object.get_if<int32_t>("episodes_released", ParseJson::not_null)),

		last_set_completed_date(object.get_if<TimestampPoint>("lastSetCompletedDate", ParseJson::exists)),
		last_set_dropped_date(object.get_if<TimestampPoint>("lastSetDroppedDate", ParseJson::exists)),
		last_set_favorite_date(object.get_if<TimestampPoint>("lastSetFavoriteDate", ParseJson::exists)),
		last_set_hold_on_date(object.get_if<TimestampPoint>("lastSetHoldOnDate", ParseJson::exists)),
		last_set_plan_date(object.get_if<TimestampPoint>("lastSetPlanDate", ParseJson::exists)),
		last_set_viewed_date(object.get_if<TimestampPoint>("lastSetViewedDate", ParseJson::exists)),
		last_set_watching_date(object.get_if<TimestampPoint>("lastSetWatchingDate", ParseJson::exists)),
		last_view_date(object.get_if<TimestampPoint>("last_view_timestamp", ParseJson::exists)),
		last_view_episode(object.get<Episode::Ptr>("last_view_episode")),

		note(object.get_if<std::string>("note", ParseJson::exists_not_null)),
		profile_list_status(object.get_if<Profile::ListStatus>("profile_list_status", ParseJson::exists_not_null)),

		is_adult(object.get<bool>("is_adult")),
		is_deleted(object.get<bool>("is_deleted")),
		is_favorite(object.get<bool>("is_favorite")),
		is_viewed(object.get<bool>("is_viewed")),
		is_play_disabled(object.get<bool>("is_play_disabled")),
		is_release_type_notifications_enabled(object.get_if<bool>("is_release_type_notifications_enabled", ParseJson::exists)),
		is_third_party_platforms_disabled(object.get_if<bool>("is_tpp_disabled", ParseJson::exists)),
		is_view_blocked(object.get_if<bool>("is_view_blocked", ParseJson::exists)),
		can_torlook_search(object.get_if<bool>("can_torlook_search", ParseJson::exists)),
		can_video_appeal(object.get_if<bool>("can_video_appeal", ParseJson::exists))
	{}

	EpisodeUpdate::EpisodeUpdate(CachingJsonObject& object) :
		last_episode_source_update_id(object.get<int64_t>("last_episode_source_update_id")),
		last_episode_type_update_id(object.get<int64_t>("last_episode_type_update_id")),
		last_episode_update_date(object.get<TimestampPoint>("last_episode_update_date")),
		last_episode_update_name(object.get_if<std::string>("last_episode_update_name", ParseJson::not_null)),
		last_episode_source_update_name(object.get<std::string>("last_episode_source_update_name")),
		last_episode_type_update_name(object.get<std::string>("lastEpisodeTypeUpdateName"))
	{}

	EpisodeSource::EpisodeSource(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		name(object.get<std::string>("name")),
		episodes_count(object.get<int64_t>("episodes_count"))
	{}

	EpisodeType::EpisodeType(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		view_count(object.get<int64_t>("view_count")),
		episodes_count(object.get<int64_t>("episodes_count")),
		name(object.get<std::string>("name")),
		workers(object.get_if<std::string>("workers", ParseJson::not_null))
	{}

	Episode::Episode(CachingJsonObject& object) :
		id(object.get_if<int64_t>("id", ParseJson::exists)),
		name(object.get_if<std::string>("name", ParseJson::not_null)),
		url(object.get<std::string>("url")),
		release_id(object.get_if<int64_t>("release_id", ParseJson::exists)),
		source_id(object.get_if<int64_t>("source_id", ParseJson::exists)),
		playback_position(object.get_if<int64_t>("playback_position", ParseJson::exists)),
		position(object.get<int32_t>("position")),

		is_watched(object.get<bool>("is_watched")),
		is_filler(object.get<bool>("is_filler"))
	{}

	ReleaseVideoCategory::ReleaseVideoCategory() :
		id(-1),
		name()
	{}

	ReleaseVideoCategory::ReleaseVideoCategory(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		name(object.get<std::string>("name"))
	{}

	ReleaseVideoHosting::ReleaseVideoHosting(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		name(object.get<std::string>("name")),
		icon_url(object.get_if<std::string>("icon", ParseJson::not_null))
	{}

	ReleaseVideo::ReleaseVideo(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		title(object.get<std::string>("title")),
		image_url(object.get<std::string>("image")),
		url(object.get<std::string>("url")),
		player_url(object.get<std::string>("player_url")),
		date(object.get<TimestampPoint>("timestamp")),
		category(object.get_if<ReleaseVideoCategory::Ptr>("category", ParseJson::not_null)),
		hosting(object.get_if<ReleaseVideoHosting::Ptr>("hosting", ParseJson::not_null)),
		profile(object.get<Profile::Ptr>("profile")),
		release(object.get<Release::Ptr>("release")),

		favorite_count(object.get<int32_t>("favorites_count")),

		is_favorite(object.get<bool>("is_favorite"))
	{}

	ReleaseVideoBlock::ReleaseVideoBlock(CachingJsonObject& object) :
		category(object.get_if<ReleaseVideoCategory::Ptr>("category", ParseJson::not_null))
	{
		object.get<CachingJsonArray>("videos").assign_to(videos);
	}

	ReleaseStreamingPlatform::ReleaseStreamingPlatform(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		name(object.get<std::string>("id")),
		icon_url(object.get_if<std::string>("icon", ParseJson::not_null)),
		url(object.get<std::string>("id"))
	{}

	ReleaseVideos::ReleaseVideos(CachingJsonObject& object) :
		release(object.get_if<Release::Ptr>("release", ParseJson::not_null)),
		blocks(object.get<CachingJsonArray>("blocks").to_vector<ReleaseVideoBlock::Ptr>()),
		last_videos(object.get<CachingJsonArray>("last_videos").to_vector<ReleaseVideo::Ptr>()),
		streaming_platforms(object.get<CachingJsonArray>("streaming_platforms").to_vector<ReleaseStreamingPlatform::Ptr>())
	{}

	Collection::Collection(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		title(object.get<std::string>("title")),
		description(object.get<std::string>("description")),
		creator(object.get<Profile::Ptr>("creator")),
		image_url(object.get<std::string>("image")),
		last_update_date(object.get<TimestampPoint>("last_update_date")),
		creation_date(object.get<TimestampPoint>("creation_date")),
		releases(object.get<CachingJsonArray>("releases").to_vector<Release::Ptr>()),

		comment_count(object.get<int64_t>("comment_count")),
		favorite_count(object.get<int32_t>("favorites_count")),

		is_favorite(object.get<bool>("is_favorite")),
		is_private(object.get<bool>("is_private"))
	{}

	Interesting::Interesting(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		type(object.get<Type>("type")),
		title(object.get<std::string>("title")),
		description(object.get<std::string>("description")),
		image_url(object.get<std::string>("image")),
		action(object.get<std::string>("action")),
		is_hidden(object.get<bool>("is_hidden"))
	{}

	LoginChange::LoginChange(CachingJsonObject& object) :
		id(object.get<int64_t>("id")),
		new_login(object.get<std::string>("newLogin")),
		date(object.get<TimestampPoint>("timestamp"))
	{}

	ProfileSocial::ProfileSocial(CachingJsonObject& object) :
		vk_page(object.get<std::string>("vk_page")),
		telegram_page(object.get<std::string>("tg_page")),
		instagram_page(object.get<std::string>("inst_page")),
		tiktok_page(object.get<std::string>("tt_page")),
		discord_page(object.get<std::string>("discord_page"))
	{}

	ProfilePreferenceStatus::ProfilePreferenceStatus(CachingJsonObject& object) :
		change_avatar_ban_expires(object.get<TimestampPoint>("ban_change_avatar_expires")),
		change_login_ban_expires(object.get<TimestampPoint>("ban_change_login_expires")),
		is_change_avatar_banned(object.get<bool>("is_change_avatar_banned")),
		is_change_login_banned(object.get<bool>("is_change_login_banned")),
		is_google_bound(object.get<bool>("is_google_bound")),
		is_vk_bound(object.get<bool>("is_vk_bound")),
		is_login_changed(object.get<bool>("is_login_changed")),
		privacy_activity(object.get<Profile::ActivityPermission>("privacy_counts")),
		privacy_friend_requests(object.get<Profile::FriendRequestPermission>("privacy_friend_requests")),
		privacy_social(object.get<Profile::SocialPermission>("privacy_social")),
		privacy_stats(object.get<Profile::StatsPermission>("privacy_stats")),
		avatar_url(object.get<std::string>("avatar")),
		status(object.get<std::string>("status")),
		vk_page(object.get<std::string>("vk_page")),
		tg_page(object.get<std::string>("tg_page"))
	{}

	LoginChangeInfo::LoginChangeInfo(CachingJsonObject& object) :
		is_change_available(object.get<bool>("is_change_available")),
		last_change_date(object.get<TimestampPoint>("last_change_at")),
		next_change_available_date(object.get<TimestampPoint>("next_change_available_at")),
		login(object.get<std::string>("login")),
		avatar_url(object.get<std::string>("avatar"))
	{}

	CollectionGetInfo::CollectionGetInfo(CachingJsonObject& object) :
		collection(object.get<Collection::Ptr>("collection")),
		watched_count(object.get<int32_t>("completedCount")),
		dropped_count(object.get<int32_t>("droppedCount")),
		hold_on_count(object.get<int32_t>("holdOnCount")),
		plan_count(object.get<int32_t>("planCount")),
		watching_count(object.get<int32_t>("watchingCount"))
	{}
};