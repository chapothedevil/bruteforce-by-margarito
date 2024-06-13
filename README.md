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
# Access
If you don't want to move into the directory againg and again and access it from anywhere in your terminal, you can move or copy this executable to the binaries directory using following command.

```bash
cp brute-force /usr/share/bin/
```

And now just type *Brute-force* in any dorectory you want, you'll be able to execute it!!!
