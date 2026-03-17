#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <src> <dst>\n", argv[0]);
        return 1;
    }

    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("open source");
        return 1;
    }

    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0) {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    char buf[1024];
    ssize_t nread;

    while ((nread = read(src_fd, buf, sizeof(buf))) > 0) {
        ssize_t nwritten = write(dst_fd, buf, nread);
        if (nwritten < 0) {
            perror("write");
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }

    if (nread < 0) {
        perror("read");
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    close(src_fd);
    close(dst_fd);
    return 0;
}
