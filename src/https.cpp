#include <errno.h>
//#include <gcrypt.h>
#include <tgbot/utils/https.h>
#include <sstream>
#include <stdexcept>

#define unused __attribute__((__unused__))

#define SEPARATE(k, sstr) \
  if (k) sstr << ','

//GCRY_THREAD_OPTION_PTHREAD_IMPL; /*deprecated*/

using namespace tgbot::utils::http;

static size_t write_data(const char *ptr, unused size_t nbs, size_t count,
                         void *dest) {
	static_cast<std::string *>(dest)->append(ptr);
	return count;
}

//static void __GnuTLS_ProvideLockingMethod() {
//	gcry_control(GCRYCTL_SET_THREAD_CBS);
//}

void tgbot::utils::http::__internal_Curl_GlobalInit() {
	if(curl_global_sslset(CURLSSLBACKEND_GNUTLS, NULL, NULL) != CURLSSLSET_OK)
		throw std::runtime_error("curl_global_sslset() error: libcurl does not support GnuTLS");

	curl_global_init(CURL_GLOBAL_SSL);
//	__GnuTLS_ProvideLockingMethod();
}

CURL *tgbot::utils::http::curlEasyInit() {
	CURL *curlInst = curl_easy_init();
	if (!curlInst) return nullptr;

	curl_easy_setopt(curlInst, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curlInst, CURLOPT_WRITEFUNCTION, write_data);

	return curlInst;
}

std::string tgbot::utils::http::get(CURL *c, const std::string &full) {
	if (!c) throw std::runtime_error("CURL is actually a null pointer :/");

	std::string body;
	curl_easy_setopt(c, CURLOPT_HTTPGET, 1L);
	curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
	curl_easy_setopt(c, CURLOPT_URL, full.c_str());

	CURLcode code = curl_easy_perform(c);
	if (code != CURLE_OK && code != CURLE_GOT_NOTHING)
		throw std::runtime_error(curl_easy_strerror(code));

	return body;
}

std::string tgbot::utils::http::multiPartUpload(CURL *c, const std::string &full, PostForms const &forms) {
	if (!c) throw std::runtime_error("CURL is actually a null pointer");

	curl_httppost *multiPost = nullptr;
	curl_httppost *end = nullptr;
	std::string body;

	for (auto const& form : forms) {
		if (!form.second.basicValue && form.second.file && form.second.mimeType)
			curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, form.first,
			             CURLFORM_CONTENTTYPE, form.second.mimeType, CURLFORM_FILE,
			             form.second.file, CURLFORM_END);
		else if (form.second.basicValue && !form.second.file && !form.second.mimeType)
			curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, form.first,
			             CURLFORM_COPYCONTENTS, form.second.basicValue, CURLFORM_END);
		else if (!form.second.basicValue && form.second.file && !form.second.mimeType)
			curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, form.first,
			             CURLFORM_FILE, form.second.file, CURLFORM_END);
		else
			throw std::runtime_error(
					std::string("This wasn't supposed to happen, please open an issue (") +
					__FILE__ + ":" + std::to_string(__LINE__)
			);
	}

	curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
	curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
	curl_easy_setopt(c, CURLOPT_URL, full.c_str());

	CURLcode code;
	if ((code = curl_easy_perform(c)) != CURLE_OK)
		throw std::runtime_error(curl_easy_strerror(code));

	return body;
}
