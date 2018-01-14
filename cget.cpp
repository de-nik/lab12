#include <iostream>
#include <thread>
#include <future>
#include <curl/curl.h>

int main(int argc, char* argv[]) {
        
        CURL* curl{ curl_easy_init() };    
	std::string url;

	if(argc < 2)
	{
		std::cout << "Enter URL: ";
		std::getline(std::cin, url);
	}
	else
	{
		url = argv[1];
	}
    
        if (curl) {

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            
            #ifdef SKIP_PEER_VERIFICATION
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            #endif
 
            #ifdef SKIP_HOSTNAME_VERIFICATION
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            #endif
 	    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
	    
	    std::promise<CURLcode> promise;
            auto response = promise.get_future();

            std::thread request([curl, &promise]() {
            	promise.set_value(curl_easy_perform(curl));
            });

            request.detach();

            auto res = response.get();
	    
	    long answer;

            if(res == CURLE_OK) {

            	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &answer);
            	std::cout << answer << std::endl;
	    }

            curl_easy_cleanup(curl);
        }
        return 0;
}
