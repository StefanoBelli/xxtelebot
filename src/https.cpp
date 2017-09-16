#include <tgbot/utils/https.h>

using namespace tgbot::utils::http;

const char* tgbot::utils::http::HttpException::what() const noexcept {
	return "Something went wrong while attempting HTTP transaction";
}

static size_t write_data(const char* ptr, size_t nbs, size_t count, void* dest) {
	static_cast<Response*>(dest)->body.append(ptr);
	return count;
}

CURL* tgbot::utils::http::curlEasyInit(const std::string& agent) {
	CURL* curlInst = curl_easy_init();
	if(!curlInst)
		return nullptr;

    curl_easy_setopt(curlInst,CURLOPT_FOLLOWLOCATION,1L);
	curl_easy_setopt(curlInst,CURLOPT_USERAGENT,agent.c_str());
	curl_easy_setopt(curlInst,CURLOPT_WRITEFUNCTION,write_data);

	return curlInst;
}

Response tgbot::utils::http::get(CURL* c, const std::string &full) {
    if(!c)
        throw HttpException();

    Response res { "", -1 };

    curl_easy_setopt(c,CURLOPT_HTTPGET,1L);
    curl_easy_setopt(c,CURLOPT_WRITEDATA,&res);
    curl_easy_setopt(c,CURLOPT_URL,full.c_str());

    if(curl_easy_perform(c) != CURLE_OK)
        throw HttpException();

    curl_easy_getinfo(c,CURLINFO_RESPONSE_CODE,&(res.code));

    return res;
}

Response tgbot::utils::http::multiPartUpload(CURL* c,
											 const std::string &operation,
                                             const int &chatId,
                                             const std::string &mimeType,
                                             const std::string &type,
                                             const std::string &filename) {
    if(!c)
        throw HttpException();

    Response res { "", -1 };
    
	curl_httppost *multiPost = nullptr;
	curl_httppost *end = nullptr;

	curl_formadd(&multiPost,&end,
			CURLFORM_COPYNAME, "chat_id",
			CURLFORM_COPYCONTENTS, std::to_string(chatId).c_str(),
			CURLFORM_END);

	curl_formadd(&multiPost,&end,
			CURLFORM_COPYNAME, type.c_str(),
			CURLFORM_CONTENTTYPE, mimeType.c_str(),
			CURLFORM_FILE,filename.c_str(),
			CURLFORM_END);

	curl_easy_setopt(c,CURLOPT_HTTPPOST,multiPost);
	curl_easy_setopt(c,CURLOPT_WRITEDATA,&res);
	curl_easy_setopt(c,CURLOPT_URL,operation.c_str());
	
    if(curl_easy_perform(c) != CURLE_OK)
        throw HttpException();

    curl_easy_getinfo(c,CURLINFO_RESPONSE_CODE,&(res.code));

    return res;
}
