# BruteForce Tool

This Bruteforce tool is under cunstruction by the developer Margarito Bonzo.
If you want to make changes to it or have way to improve it, please do consider making it possible.

## For test run, execute the following commands in your terminal

```bash
mkdir -p build
cd build
cmake ..
make
```
## Usage
```bash
./brute-force --usr target_username --pswd passwords.txt --req http-post-form --url "http://example.com/login?username=^USERNAME^&password=^PASSWORD^:btn=Sign+In:Invalid Login!"
```
