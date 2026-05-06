#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/if_alg.h>
#include <sys/socket.h>

int main() {
	int fd, ret;
	struct sockaddr_alg alg;

	fd = socket(AF_ALG, SOCK_SEQPACKET, 0);
	if (fd < 0) {
		printf("socket failed: %s\n", strerror(fd));
		exit(1);
	}

	alg.salg_family = AF_ALG;
	sprintf((char *)alg.salg_type, "aead");
	alg.salg_feat = 2;
	alg.salg_mask = 42;
	sprintf((char *)alg.salg_name, "authencesn(hmac(sha256),cbc(aes))");

	ret = bind(fd, (struct sockaddr *)&alg, sizeof(alg));

	if (ret < 0) {
		printf("bind failed: %s\n", strerror(ret));
		exit(2);
	}

	printf("done!\n");
	close(fd);
	return 0;
}

