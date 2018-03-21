FROM buildpack-deps:latest

ENV LIB_CHECK_VERSION 0.12.0

WORKDIR /tmp/check
RUN curl -L https://github.com/libcheck/check/releases/download/${LIB_CHECK_VERSION}/check-${LIB_CHECK_VERSION}.tar.gz | tar xvz

WORKDIR check-${LIB_CHECK_VERSION}
RUN ./configure && \
  make && \
  make check && \
  make install && \
  ldconfig

WORKDIR /
RUN rm -R /tmp/check
