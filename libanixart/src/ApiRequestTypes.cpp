#include <anixart/ApiRequestTypes.hpp>
#include <netsess/JsonTools.hpp>

namespace anixart::requests {
	using network::json::InlineJson;
	using aux::to_string;

    std::string FilterRequest::serialize() const {
        std::string json;
        InlineJson::open_object(json);
		InlineJson::append(json, "category_id", category);
		InlineJson::append(json, "country", country);
		InlineJson::append(json, "start_year", start_year);
		InlineJson::append(json, "end_year", end_year);
		InlineJson::append(json, "episode_duration_from", episode_duration_from);
		InlineJson::append(json, "episode_duration_to", episode_duration_to);
		InlineJson::append(json, "episodes_from", episodes_count_from);
		InlineJson::append(json, "episodes_to", episodes_count_to);
		InlineJson::append(json, "season", season);
		InlineJson::append(json, "status_id", status);
		InlineJson::append(json, "studio", studio);
		InlineJson::append(json, "sort", sort);
		InlineJson::append(json, "is_genres_exclude_mode_enabled", is_genres_exclude_mode);
		InlineJson::append(json, "genres", genres);
		InlineJson::append(json, "profile_list_exclusions", profile_list_exclusions);
		InlineJson::append(json, "types", types);
		InlineJson::append(json, "age_ratings", age_ratings);
		InlineJson::close_object(json);
		return json;
    }
	std::string SearchRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "query", query);
		InlineJson::append(json, "searchBy", search_by);
		InlineJson::close_object(json);
		return json;
	}
	std::string DirectLinkRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "url", url);
		InlineJson::close_object(json);
		return json;
	}
	std::string ReleaseReportRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "message", message);
		InlineJson::append(json, "reason", reason);
		InlineJson::close_object(json);
		return json;
	}
	std::string ProfileProcessRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "banExpires", ban_expires);
		InlineJson::append(json, "banReason", ban_reason);
		InlineJson::append(json, "isBanned", is_banned);
		InlineJson::close_object(json);
		return json;
	}
	std::string PrivacyEditRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "permission", permission);
		InlineJson::close_object(json);
		return json;
	}
	SocialPagesEditRequest::SocialPagesEditRequest(const ProfileSocial& social) :
		discord_page(social.discord_page),
		instagram_page(social.instagram_page),
		telegram_page(social.telegram_page),
		tiktok_page(social.tiktok_page),
		vk_page(social.vk_page)
	{}
	std::string SocialPagesEditRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "discordPage", discord_page);
		InlineJson::append(json, "instPage", instagram_page);
		InlineJson::append(json, "tgPage", telegram_page);
		InlineJson::append(json, "ttPage", tiktok_page);
		InlineJson::append(json, "vkPage", vk_page);
		InlineJson::close_object(json);
		return json;
	}
	std::string StatusEditRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "status", status);
		InlineJson::close_object(json);
		return json;
	}
	std::string CommentAddRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "spoiler", is_spoiler);
		InlineJson::append(json, "message", message);
		InlineJson::append(json, "parentCommentId", parent_comment_id);
		InlineJson::append(json, "replyToProfileId", reply_to_profile_id);
		InlineJson::close_object(json);
		return json;
	}
	std::string CommentEditRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "spoiler", is_spoiler);
		InlineJson::append(json, "message", message);
		InlineJson::close_object(json);
		return json;
	}
	std::string CommentProcessRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "isSpoiler", is_spoiler);
		InlineJson::append(json, "isDeleted", is_deleted);
		InlineJson::append(json, "isBanned", is_banned);
		InlineJson::append(json, "banReason", ban_reason);
		InlineJson::append(json, "banExpires", ban_expires);
		InlineJson::close_object(json);
		return json;
	}
	std::string CommentReportRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "message", message);
		InlineJson::append(json, "reason", reason);
		InlineJson::close_object(json);
		return json;
	}
	std::string ReleaseVideoAppealRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "releaseId", release_id);
		InlineJson::append(json, "categoryId", category_id);
		InlineJson::append(json, "title", title);
		InlineJson::append(json, "url", url);
		InlineJson::close_object(json);
		return json;
	}
	std::string CollectionReportRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "message", message);
		InlineJson::append(json, "reason", reason);
		InlineJson::close_object(json);
		return json;
	}
	std::string CreateEditCollectionRequest::serialize() const {
		std::string json;
		InlineJson::open_object(json);
		InlineJson::append(json, "title", title);
		InlineJson::append(json, "description", description);
		InlineJson::append(json, "releases", release_ids);
		InlineJson::append(json, "is_private", is_private);
		InlineJson::close_object(json);
		return json;
	}
};
