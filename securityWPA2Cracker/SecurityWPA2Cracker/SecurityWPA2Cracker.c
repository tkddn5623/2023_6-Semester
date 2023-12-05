#include <openssl/sha.h>

int main() {
    SHA_CTX sha1_ctx;
    SHA1_Init(&sha1_ctx);
    // SHA1 컨텍스트를 초기화하고 데이터를 입력하기 위한 준비
    // 필요한 경우 SHA1_Update 함수로 데이터를 추가로 입력할 수 있음
    printf("정상 초기화\n");
    return 0;
}