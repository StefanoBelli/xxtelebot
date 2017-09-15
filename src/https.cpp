#include <curl/curl.h>
#include <tgbot/utils/https.h>

static CURL* gCurlInst = nullptr;

using namespace tgbot::utils::http;

const char* HttpException::what() const noexcept {
	return "Something went wrong while attempting HTTP transaction";
}

size_t write_data(const char* ptr, size_t nbs, size_t count, void* dest) {
	static_cast<Response*>(dest)->body.append(ptr);
	return count;
}

//!!No locking protection!!
bool tgbot::utils::http::globalCurlInitializer(const std::string& agent) {
	gCurlInst = curl_easy_init();
	if(!gCurlInst)
		return false;

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
