//atomic
#include <curl/curl.h>
#include <tgbot/utils/https.h>

static CURL* gCurlInst = nullptr;

using namespace tgbot::utils::http;

const char* tgbot::utils::http::HttpException::what() const noexcept {
	return "Something went wrong while attempting HTTP transaction";
}

static size_t write_data(const char* ptr, size_t nbs, size_t count, void* dest) {
	static_cast<Response*>(dest)->body.append(ptr);
	return count;
}

//!!No locking protection!!
bool tgbot::utils::http::globalCurlInitializer(const std::string& agent) {
	gCurlInst = curl_easy_init();
	if(!gCurlInst)
		return false;

    curl_easy_setopt(gCurlInst,CURLOPT_FOLLOWLOCATION,1L);
	curl_easy_setopt(gCurlInst,CURLOPT_TCP_KEEPALIVE,1L);
	curl_easy_setopt(gCurlInst,CURLOPT_TCP_KEEPINTVL,60);
	curl_easy_setopt(gCurlInst,CURLOPT_USERAGENT,agent.c_str());
	curl_easy_setopt(gCurlInst,CURLOPT_WRITEFUNCTION,write_data);

	return true;
}

//!!No locking protection!!
bool tgbot::utils::http::globalCurlCleanup() {
	if(!gCurlInst)
		return false;

	curl_easy_cleanup(gCurlInst);
	return true;
}

Response tgbot::utils::http::get(const std::string &full) {
    if(!gCurlInst)
        throw HttpException();

    Response res { "", -1 };

    curl_easy_setopt(gCurlInst,CURLOPT_HTTPGET,1L);
    curl_easy_setopt(gCurlInst,CURLOPT_WRITEDATA,&res);
    curl_easy_setopt(gCurlInst,CURLOPT_URL,full.c_str());

    if(curl_easy_perform(gCurlInst) != CURLE_OK)
        throw HttpException();

    curl_easy_getinfo(gCurlInst,CURLINFO_RESPONSE_CODE,&(res.code));

    return res;
}

Response tgbot::utils::http::multiPartUpload(const std::string &operation,
                                             const int &chatId,
                                             const std::string &mimeType,
                                             const std::string &filename) {
    if(!gCurlInst)
        throw HttpException();

    Response res { "", -1 };

	curl_httppost *multiPost = nullptr;
	curl_httppost *end = nullptr;

	//formadd
	//formadd
	

	curl_easy_setopt(gCurlInst,CURLOPT_HTTPPOST,multiPost);
	curl_easy_setopt(gCurlInst,CURLOPT_WRITEDATA,&res);
	curl_easy_setopt(gCurlInst,CURLOPT_URL,operation.c_str());
	
    if(curl_easy_perform(gCurlInst) != CURLE_OK)
        throw HttpException();

    curl_easy_getinfo(gCurlInst,CURLINFO_RESPONSE_CODE,&(res.code));

    return res;
}
