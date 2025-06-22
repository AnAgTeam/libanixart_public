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

#if __has_include("Secrets.hpp")
#include "Secrets.hpp"
#endif


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

void print_article_block_info(ArticleParagraphBlock::Ptr paragraph_block) {
    std::cout << "(ParagraphBlock): id=" << paragraph_block->id << ", Text=" << paragraph_block->text << std::endl;
}
void print_article_block_info(ArticleMediaBlock::Ptr media_block) {
    std::cout << "(MediaBlock) id=" << media_block->id << std::endl;
    for (auto& media_file : media_block->items) {
        std::cout << "* (MediaFile): uuid=" << media_file->uuid << ", url=" << media_file->url << std::endl;
    }
}
void print_article_block_info(ArticleHeaderBlock::Ptr header_block) {
    std::cout << "(HeaderBlock): id=" << header_block->id << ", Text=" << header_block->text << ", level=" << header_block->level << std::endl;
}

void print_article_info(Article::Ptr article) {
    std::cout << "Article: author=" << article->author->username << std::endl;
    for (size_t i = 0; i < article->payload->blocks.size(); ++i) {
        auto& block_variant = article->payload->blocks[i];

        std::cout << "[" << i << "] ";
        switch (block_variant.which()) {
        case ArticlePayload::block_magic<ArticleParagraphBlock>():
            print_article_block_info(variant_get<ArticleParagraphBlock::Ptr>(block_variant));
            break;
        case ArticlePayload::block_magic<ArticleMediaBlock>():
            print_article_block_info(variant_get<ArticleMediaBlock::Ptr>(block_variant));
            break;
        case ArticlePayload::block_magic<ArticleHeaderBlock>():
            print_article_block_info(variant_get<ArticleHeaderBlock::Ptr>(block_variant));
            break;
        }
    }
}

void test_articles(Api& api) {
    ArticlesFilterRequest article_request;
    article_request.channel_id = ChannelID(662);
    article_request.date_filter = ArticlesFilterRequest::DateFilter::AllTime;

    std::vector<Article::Ptr> articles = api.articles().articles(article_request, 0)->get();

    print_article_info(articles[0]);
}

int main() {
    (void)_setmode(_fileno(stdin), _O_WTEXT);
    SetConsoleOutputCP(CP_UTF8);

    network::UrlSession::init();

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

        Parsers parsers;
        ReleaseID rel_id = static_cast<ReleaseID>(18442);

        //Article::Ptr article = api.articles().get_article(ArticleID(96713));

        //std::vector<Profile::Ptr> my_friends = api.profiles().get_friends(my_profile_id, 0)->get();
        //Channel::Ptr friend_blog = api.articles().get_blog_channel(my_friends[10]->id);

        ChannelID friend_blog_id(4813);

        //ArticlesFilterRequest articles_request;
        //articles_request.channel_id = friend_blog_id;

        //for (auto article : api.articles().articles(articles_request, 0)->get()) {
        //    static int i = 0;
        //    std::cout << "Article (" << i++ << ") id=" << static_cast<int64_t>(article->id) << std::endl;
        //    print_article_info(article);
        //}

        //ArticlesFilterRequest articles_request;
        //articles_request.channel_id = friend_blog->id;

        //std::vector<Article::Ptr> blog_articles = api.articles().articles(articles_request, 0)->get();

        //Article::Ptr article = api.articles().get_article(ArticleID(97400));

        //Channel::Ptr my_channel = api.articles().get_blog_channel(my_profile_id);

        ChannelID my_channel_id(4714);

        std::string media_upload_token = api.articles().get_channel_media_token(my_channel_id, false, true);

        //auto header_block = std::make_shared<ArticleHeaderBlock>(ArticleBlock::get_random_uuid());
        //header_block->text = "Жиза";
        //header_block->level = 3;

        //MediaFile::Ptr media_file = api.articles().upload_media_file(R"(E:\misc\screenshort_i_1.jpg)", media_upload_token);

        //auto media_block = std::make_shared<ArticleMediaBlock>(ArticleBlock::get_random_uuid());
        //media_block->items.push_back(media_file);

        ////auto unsupp_block = std::make_shared<ArticleUnsupportedBlock>(ArticleBlock::get_random_uuid());
        
        //ArticlePayload payload;
        //payload.date = std::chrono::time_point_cast<TimestampDuration>(std::chrono::system_clock::now());
        //payload.blocks.push_back(header_block);
        //payload.blocks.push_back(media_block);

        ArticleCreateEditRequest create_request;
        //create_request.payload = payload.serialize();
        //create_request.repost_article_id = ArticleID(99995);
        //create_request.payload = R"({"blocks":[{"id":"0b68fcc4-4df","name":"embed","type":"embed","data":{"title":"СМЕШАРИКИ - ОГУРЕЦ PHONK (ПРЕМЬЕРА КЛИПА 2024) [ля]","description":"Слушать альбом \"ля\": https://band.link/lyaaТы чувствуешь вкус настоящей жизни, потому что у тебя есть он… новый фонк-альбом от Смешариков. В нём есть всё: ле...","embed":"https://www.youtube.com/embed/nETEGKpqs9M","hash":"5131e0f5c37751ae8b3be58d34bdc04fde1d421f","image":"https://i.ytimg.com/vi/nETEGKpqs9M/maxresdefault.jpg","service":"youtube","site_name":"YouTube","url":"https://www.youtube.com/watch?v=nETEGKpqs9M&list=RDnETEGKpqs9M&start_radio=1","height":720,"width":1280}}],"block_count":1,"time":1750356436,"version":"2.26.5"})";
        //create_request.payload = R"({"blocks":[{"id":"0b68fcb4-4df","name":"embed","type":"embed","data":{"title":"СМЕШАРИКИ - ОГУРЕЦ PHONK (ПРЕМЬЕРА КЛИПА 2024) [ля]","description":"Слушать альбом \"ля\": https://band.link/lyaaТы чувствуешь вкус настоящей жизни, потому что у тебя есть он… новый фонк-альбом от Смешариков. В нём есть всё: ле...","embed":"https://www.youtube.com/embed/nETEGKpqs9M","hash":"5131e0f5c37751ae8b3be58d34bdc04fde1d421f","image":"https://i.ytimg.com/vi/nETEGKpqs9M/maxresdefault.jpg","service":"youtube","site_name":"YouTube","url":"https://www.youtube.com/watch?v=nETEGKpqs9M&list=RDnETEGKpqs9M&start_radio=1","height":720,"width":1280}},{"id":"0b68fcb4-4da","name":"media","type":"media","data":{"items":[{"id":"a98c9726-08c8-483e-b741-9fc537f7b80e","hash":"29077b25d8f0f2b832a354425a3604c7e0913ceb","url":"https://s3.anixstatic.com/images/a98c9726-08c8-483e-b741-9fc537f7b80e_N1BXH.jpg","height":512,"width":512}],"item_count":1}},{"id":"0b68fcb4-6df","name":"paragraph","type":"paragraph","data":{"text":"Вот она - истина","text_length":28}}],"block_count":3,"time":1750348705000,"version":"2.26.5"})";
        //create_request.payload = R"({"blocks":[{"id":"0b68fcb4-4da","name":"media","type":"media","data":{"items":[{"id":"a98c9726-08c8-483e-b741-9fc537f7b80e","hash":"29077b25d8f0f2b832a354425a3604c7e0913ceb","url":"https://s3.anixstatic.com/images/a98c9726-08c8-483e-b741-9fc537f7b80e_N1BXH.jpg","height":512,"width":512}],"item_count":1}},{"id":"0b68fcb4-6df","name":"paragraph","type":"paragraph","data":{"text":"Вот она - истина","text_length":28}}],"block_count":2,"time":1750348705000,"version":"2.26.5"})";
        //create_request.payload = R"({"blocks":[{"id":"a0971e2e-fa6","name":"paragraph","type":"paragraph","data":{"text":"123","text_length":3}}],"block_count":1,"time":1750347291000,"version":"2.26.5"})";
        //create_request.payload = R"(ArticlePayload(time=1750345705, version="2.26.5", blocks=[ArticleParagraphData(text="123", textLength=28)], blockCount=1))";
        //create_request.payload = R"(ArticlePayload(time=1750345705,version=2.26.5,blocks=[ArticleEmbedData(hash=5131e0f5c37751ae8b3be58d34bdc04fde1d421f,url=https://www.youtube.com/watch?v=nETEGKpqs9M&list=RDnETEGKpqs9M&start_radio=1,service=youtube,siteName=YouTube,title=СМЕШАРИКИ - ОГУРЕЦ PHONK (ПРЕМЬЕРА КЛИПА 2024) [ля],description=Слушать альбом "ля": https://band.link/lyaaТы чувствуешь вкус настоящей жизни, потому что у тебя есть он… новый фонк-альбом от Смешариков. В нём есть всё: ле...,width=1280,height=720,image=https://i.ytimg.com/vi/nETEGKpqs9M/maxresdefault.jpg,embed=https://www.youtube.com/embed/nETEGKpqs9M),ArticleMediaData(items=[MediaFile(id=c7a063cb-7d49-4a5a-a5c2-4bf03a4ad37a,hash=65bdf104a8abd4c6c89c6226f7fa907531d7ea3e,url=https://s3.anixstatic.com/images/c7a063cb-7d49-4a5a-a5c2-4bf03a4ad37a_MvFeV.jpg,width=512,height=512)],itemCount=1),ArticleParagraphData(text=Вот она - истина,textLength=28)],blockCount=3))";

        api.articles().create_article(my_channel_id, create_request);

        //print_article_info(article);

        //auto [someone_profile, _] = api.profiles().get_profile(ProfileID(171123));
    
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
