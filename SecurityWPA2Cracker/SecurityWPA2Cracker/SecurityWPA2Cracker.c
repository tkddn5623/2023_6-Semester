#include <openssl/sha.h>

int main() {
    SHA_CTX sha1_ctx;
    SHA1_Init(&sha1_ctx);
    // SHA1 ���ؽ�Ʈ�� �ʱ�ȭ�ϰ� �����͸� �Է��ϱ� ���� �غ�
    // �ʿ��� ��� SHA1_Update �Լ��� �����͸� �߰��� �Է��� �� ����
    printf("���� �ʱ�ȭ\n");
    return 0;
}