#include <tgbot/utils/https.h>

using namespace tgbot::utils;

HttpsException::HttpsException(const char *message) :
	failureMessage(message) {}

const char* HttpsException::what() const noexcept {
	return failureMessage;
}

static size_t write(const char* buf, size_t s, size_t nmemb, void* stream) {
	static_cast<HttpResponse*>(stream)->body.append(buf);
	return nmemb;
}

Https::Https() {
	curlinst = curl_easy_init();
	if(!curlinst)
		throw HttpsException("Cannot initialize curl easy interface");

	curl_easy_setopt(curlinst,CURLOPT_FOLLOWLOCATION,1L);
	curl_easy_setopt(curlinst,CURLOPT_TCP_KEEPALIVE,1L);
	curl_easy_setopt(curlinst,CURLOPT_TCP_KEEPINTVL,60);
	curl_easy_setopt(curlinst,CURLOPT_WRITEFUNCTION,write);
}

Https::~Https() {
	if(curlinst)
		curl_easy_cleanup(curlinst);
}

HttpResponse Https::get(const std::string &fullUrl) {
	HttpResponse response { "",-1 };

	curl_easy_setopt(curlinst,CURLOPT_URL,fullUrl.c_str());
	curl_easy_setopt(curlinst,CURLOPT_WRITEDATA,&response);

	CURLcode curlcode;
	if((curlcode=curl_easy_perform(curlinst)) != CURLE_OK)
		throw HttpsException(curl_easy_strerror(curlcode));

	curl_easy_getinfo (curlinst, CURLINFO_RESPONSE_CODE,
			&(response.code));

	return response;
}

HttpResponse Https::multiPartUpload(const std::string &fullUrl, const std::string &localFileName,
		std::ifstream &stream) {

}
