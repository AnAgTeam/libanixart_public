#include "pch.h"
#include <anixart/Random.hpp>

using namespace network;
using namespace anixart;
using namespace anixart::random;
using namespace anixart::json;

#pragma execution_character_set("utf-8")

std::string_view expected_random_uuid = "AAAAAAAAAAA";

// JsonObject is "tested"

TEST_CASE("gen_random_string(...)") {
	REQUIRE(gen_random_string(192ULL, ascii).length() == 192ULL);
}

TEST_CASE("Random block uuid generation") {
	REQUIRE(ArticleBlock::get_random_uuid() == expected_random_uuid);
	REQUIRE(ArticleBlock::get_random_uuid().length() == 11);
}

TEST_CASE("ArticleParagraphBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"paragraph","type":"paragraph","data":{"text":"hello, world!","text_length":13}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	ArticleParagraphBlock block(ArticleBlock::get_random_uuid());

	block.text = "hello, world!";

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("ArticleQuoteBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"quote","type":"quote","data":{"text":"123123","text_length":6,"alignment":"center","caption":"123123","caption_length":6}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	ArticleQuoteBlock block(ArticleBlock::get_random_uuid());

	block.caption = "123123";
	block.text = "123123";
	block.alignment = ArticleQuoteBlock::Alignment::Center;

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("ArticleDelimiterBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"delimiter","type":"delimiter","data":{}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	ArticleDelimiterBlock block(ArticleBlock::get_random_uuid());

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("ArticleHeaderBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"header","type":"header","data":{"level":3,"text":"123123","text_length":6}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	ArticleHeaderBlock block(ArticleBlock::get_random_uuid());

	block.level = 3;
	block.text = "123123";

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("MediaFile serialization") {
	std::string_view expected_serialized = R"({"id":"aaaa-aaaaaa-aa-aa","hash":"fdsfdsfsdfsdfsdfsdffff","url":"https://anixstatic.blabla.com/file?hash=ffff","height":1080,"width":900099})";
	JsonObject expected_object = parse_json(expected_serialized);

	MediaFile media_file;

	media_file.hash = "fdsfdsfsdfsdfsdfsdffff";
	media_file.url = "https://anixstatic.blabla.com/file?hash=ffff";
	media_file.height = 1080;
	media_file.width = 900099;
	media_file.uuid = "aaaa-aaaaaa-aa-aa";

	JsonObject object = parse_json(media_file.serialize());
	REQUIRE(object == expected_object);
}

TEST_CASE("ArticleMediaBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"media","type":"media","data":{"items":[{"id":"aaaa-aaaaaa-aa-aa","hash":"fdsfdsfsdfsdfsdfsdffff","url":"https://anixstatic.blabla.com/file?hash=ffff","height":1080,"width":900099}],"item_count":1}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	auto media_file = std::make_shared<MediaFile>();
	media_file->hash = "fdsfdsfsdfsdfsdfsdffff";
	media_file->url = "https://anixstatic.blabla.com/file?hash=ffff";
	media_file->height = 1080;
	media_file->width = 900099;
	media_file->uuid = "aaaa-aaaaaa-aa-aa";

	ArticleMediaBlock block(ArticleBlock::get_random_uuid());
	block.items.push_back(media_file);

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("ArticleEmbedBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"embed","type":"embed","data":{"title":"СМЕШАРИКИ - ОГУРЕЦ PHONK (ПРЕМЬЕРА КЛИПА 2024) [ля]","description":"Слушать альбом \"ля\": https://band.link/lyaaТы чувствуешь вкус настоящей жизни, потому что у тебя есть он… новый фонк-альбом от Смешариков. В нём есть всё: ле...","embed":"https://www.youtube.com/embed/nETEGKpqs9M","hash":"5131e0f5c37751ae8b3be58d34bdc04fde1d421f","image":"https://i.ytimg.com/vi/nETEGKpqs9M/maxresdefault.jpg","service":"youtube","site_name":"YouTube","url":"https://www.youtube.com/watch?v=nETEGKpqs9M&list=RDnETEGKpqs9M&start_radio=1","height":720,"width":1280}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	ArticleEmbedBlock block(ArticleBlock::get_random_uuid());
	block.title = "СМЕШАРИКИ - ОГУРЕЦ PHONK (ПРЕМЬЕРА КЛИПА 2024) [ля]";
	block.description = "Слушать альбом \"ля\": https://band.link/lyaaТы чувствуешь вкус настоящей жизни, потому что у тебя есть он… новый фонк-альбом от Смешариков. В нём есть всё: ле...";
	block.embed_url = "https://www.youtube.com/embed/nETEGKpqs9M";
	block.image_url = "https://i.ytimg.com/vi/nETEGKpqs9M/maxresdefault.jpg";
	block.url = "https://www.youtube.com/watch?v=nETEGKpqs9M&list=RDnETEGKpqs9M&start_radio=1";
	block.hash = "5131e0f5c37751ae8b3be58d34bdc04fde1d421f";
	block.service = "youtube";
	block.site_name = "YouTube";
	block.height = 720;
	block.width = 1280;

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("ArticleListBlock serialization") {
	std::string_view expected_serialized = R"({"id":"AAAAAAAAAAA","name":"list","type":"list","data":{"items":["123123123\r","444444"],"item_count":2,"style":"ordered"}})";
	JsonObject expected_block_object = parse_json(expected_serialized);

	ArticleListBlock block(ArticleBlock::get_random_uuid());
	block.items.push_back("123123123\r");
	block.items.push_back("444444");
	block.style = ArticleListBlock::Style::Ordered;

	JsonObject block_object = parse_json(block.serialize());
	REQUIRE(block_object == expected_block_object);
}

TEST_CASE("ArticlePayload serialization") {
	std::string_view expected_serialized =
		R"({"blocks":[)"
		R"({"id":"AAAAAAAAAAA","name":"header","type":"header","data":{"level":3,"text":"123123","text_length":6}},)"
		R"({"id":"AAAAAAAAAAA","name":"media","type":"media","data":{"items":[{"id":"aaaa-aaaaaa-aa-aa","hash":"fdsfdsfsdfsdfsdfsdffff","url":"https://anixstatic.blabla.com/file?hash=ffff","height":1080,"width":900099}],"item_count":1}},)"
		R"({"id":"AAAAAAAAAAA","name":"delimiter","type":"delimiter","data":{}})"
		R"(],"block_count":3,"version":"2.26.5","time":100})";
	JsonObject expected_object = parse_json(expected_serialized);

	auto delim_block = std::make_shared<ArticleDelimiterBlock>(ArticleBlock::get_random_uuid());

	auto header_block = std::make_shared<ArticleHeaderBlock>(ArticleBlock::get_random_uuid());
	header_block->level = 3;
	header_block->text = "123123";

	auto media_file = std::make_shared<MediaFile>();
	media_file->hash = "fdsfdsfsdfsdfsdfsdffff";
	media_file->url = "https://anixstatic.blabla.com/file?hash=ffff";
	media_file->height = 1080;
	media_file->width = 900099;
	media_file->uuid = "aaaa-aaaaaa-aa-aa";

	auto media_block = std::make_shared<ArticleMediaBlock>(ArticleBlock::get_random_uuid());
	media_block->items.push_back(media_file);

	ArticlePayload payload;
	payload.blocks.push_back(header_block);
	payload.blocks.push_back(media_block);
	payload.blocks.push_back(delim_block);
	payload.date = TimestampPoint{} + std::chrono::seconds(100);

	JsonObject object = parse_json(payload.serialize());
	REQUIRE(object == expected_object);
}


TEST_CASE("ArticlePayload blocks types deserialization") {
	std::string_view blocks =
		R"({"blocks":[)"
		R"({"id":"AAAAAAAAAAA","name":"header","type":"header","data":{"level":3,"text":"123123","text_length":6}},)"
		R"({"id":"AAAAAAAAAAA","name":"media","type":"media","data":{"items":[{"id":"aaaa-aaaaaa-aa-aa","hash":"fdsfdsfsdfsdfsdfsdffff","url":"https://anixstatic.blabla.com/file?hash=ffff","height":1080,"width":900099}],"item_count":1}},)"
		R"({"id":"AAAAAAAAAAA","name":"delimiter","type":"delimiter","data":{}},)"
		R"({"id":"AAAAAAAAAAA","name":"list","type":"list","data":{"items":["123123123\r","444444"],"item_count":2,"style":"ordered"}},)"
		R"({"id":"AAAAAAAAAAA","name":"embed","type":"embed","data":{"title":"СМЕШАРИКИ - ОГУРЕЦ PHONK (ПРЕМЬЕРА КЛИПА 2024) [ля]","description":"Слушать альбом \"ля\": https://band.link/lyaaТы чувствуешь вкус настоящей жизни, потому что у тебя есть он… новый фонк-альбом от Смешариков. В нём есть всё: ле...","embed":"https://www.youtube.com/embed/nETEGKpqs9M","hash":"5131e0f5c37751ae8b3be58d34bdc04fde1d421f","image":"https://i.ytimg.com/vi/nETEGKpqs9M/maxresdefault.jpg","service":"youtube","site_name":"YouTube","url":"https://www.youtube.com/watch?v=nETEGKpqs9M&list=RDnETEGKpqs9M&start_radio=1","height":720,"width":1280}},)"
		R"({"id":"AAAAAAAAAAA","name":"quote","type":"quote","data":{"text":"123123","text_length":6,"alignment":"center","caption":"123123","caption_length":6}},)"
		R"({"id":"AAAAAAAAAAA","name":"blabla","type":"blabla","data":{}})"
		R"(],"block_count":7,"version":"2.26.5","time":100})";
	CachingJsonObject blocks_object = parse_json(blocks);

	ArticlePayload payload(blocks_object);

	REQUIRE(payload.blocks[0].which() == ArticlePayload::block_magic<ArticleHeaderBlock>());
	REQUIRE(payload.blocks[1].which() == ArticlePayload::block_magic<ArticleMediaBlock>());
	REQUIRE(payload.blocks[2].which() == ArticlePayload::block_magic<ArticleDelimiterBlock>());
	REQUIRE(payload.blocks[3].which() == ArticlePayload::block_magic<ArticleListBlock>());
	REQUIRE(payload.blocks[4].which() == ArticlePayload::block_magic<ArticleEmbedBlock>());
	REQUIRE(payload.blocks[5].which() == ArticlePayload::block_magic<ArticleQuoteBlock>());
	REQUIRE(payload.blocks[6].which() == ArticlePayload::block_magic<ArticleUnsupportedBlock>());
}