FROM ubuntu:22.04

RUN apt update && apt install --yes ca-certificates wget && \
    wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
    echo 'deb [trusted=yes] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-18 main' >> /etc/apt/sources.list && \
    apt update && apt install --yes clang-18 libc++-18-dev libc++abi-18-dev lld-18 

ENTRYPOINT [ "/bin/bash" ]
