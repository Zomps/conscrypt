/* Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

/* This program generates output that is expected to become
 * NativeConstants.java. This reifies several OpenSSL constants into Java. */

#include <stdio.h>

#include <openssl/ec.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#include <openssl/evp.h>
#if defined(OPENSSL_IS_BORINGSSL)
#include <openssl/aead.h>
#endif

static const char kCopyright[] =
    "/* Copyright (C) 2015 The Android Open Source Project\n"
    " *\n"
    " * Licensed under the Apache License, Version 2.0 (the \"License\");\n"
    " * you may not use this file except in compliance with the License.\n"
    " * You may obtain a copy of the License at\n"
    " *\n"
    " *      http://www.apache.org/licenses/LICENSE-2.0\n"
    " *\n"
    " * Unless required by applicable law or agreed to in writing, software\n"
    " * distributed under the License is distributed on an \"AS IS\" BASIS,\n"
    " * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or "
    "implied.\n"
    " * See the License for the specific language governing permissions and\n"
    " * limitations under the License. */\n";

int main(int /* argc */, char ** /* argv */) {
  printf("%s\n", kCopyright);
  printf("/* This file was generated by generate_constants.cc. */\n\n");
  printf("package org.conscrypt;\n\n");
  printf("public final class NativeConstants {\n");

  printf("    public static final boolean HAS_EVP_AEAD = %s;\n",
#if defined(EVP_AEAD_DEFAULT_TAG_LENGTH)
         "true"
#else
         "false"
#endif
  );

#define CONST(x) \
  printf("    public static final int %s = %ld;\n", #x, (long int)x)
#define CONST_MINUS_1(x) printf("    public static final int %s = -1;\n", #x)
  CONST(OPENSSL_EC_NAMED_CURVE);

  CONST(POINT_CONVERSION_COMPRESSED);
  CONST(POINT_CONVERSION_UNCOMPRESSED);

  CONST(EXFLAG_CA);
  CONST(EXFLAG_CRITICAL);

  CONST(EVP_PKEY_RSA);
  CONST(EVP_PKEY_HMAC);
  CONST(EVP_PKEY_EC);

  CONST(RSA_PKCS1_PADDING);
  CONST(RSA_NO_PADDING);
  CONST(RSA_PKCS1_OAEP_PADDING);

  CONST(SSL_MODE_SEND_FALLBACK_SCSV);
  CONST(SSL_MODE_CBC_RECORD_SPLITTING);
  CONST(SSL_MODE_HANDSHAKE_CUTTHROUGH);

  CONST(SSL_OP_NO_TICKET);
  CONST(SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION);
  CONST(SSL_OP_NO_SSLv3);
  CONST(SSL_OP_NO_TLSv1);
  CONST(SSL_OP_NO_TLSv1_1);
  CONST(SSL_OP_NO_TLSv1_2);

  CONST(SSL_SENT_SHUTDOWN);
  CONST(SSL_RECEIVED_SHUTDOWN);

  CONST(TLS_CT_RSA_SIGN);
  CONST(TLS_CT_ECDSA_SIGN);

#if defined(TLS_CT_RSA_FIXED_DH)
  CONST(TLS_CT_RSA_FIXED_DH);
#else
  CONST_MINUS_1(TLS_CT_RSA_FIXED_DH);
#endif
#if defined(TLS_CT_RSA_FIXED_ECDH)
  CONST(TLS_CT_RSA_FIXED_ECDH);
#else
  CONST_MINUS_1(TLS_CT_RSA_FIXED_ECDH);
#endif
#if defined(TLS_CT_ECDSA_FIXED_ECDH)
  CONST(TLS_CT_ECDSA_FIXED_ECDH);
#else
  CONST_MINUS_1(TLS_CT_ECDSA_FIXED_ECDH);
#endif

  CONST(SSL_VERIFY_NONE);
  CONST(SSL_VERIFY_PEER);
  CONST(SSL_VERIFY_FAIL_IF_NO_PEER_CERT);

  CONST(SSL_ST_CONNECT);
  CONST(SSL_ST_ACCEPT);
  CONST(SSL_ST_MASK);
  CONST(SSL_ST_INIT);
  CONST(SSL_ST_OK);
  CONST(SSL_ST_RENEGOTIATE);
  CONST(SSL_CB_LOOP);
  CONST(SSL_CB_EXIT);
  CONST(SSL_CB_READ);
  CONST(SSL_CB_WRITE);
  CONST(SSL_CB_ALERT);
  CONST(SSL_CB_READ_ALERT);
  CONST(SSL_CB_WRITE_ALERT);
  CONST(SSL_CB_ACCEPT_LOOP);
  CONST(SSL_CB_ACCEPT_EXIT);
  CONST(SSL_CB_CONNECT_LOOP);
  CONST(SSL_CB_CONNECT_EXIT);
  CONST(SSL_CB_HANDSHAKE_START);
  CONST(SSL_CB_HANDSHAKE_DONE);

  CONST(SSL3_RT_MAX_PACKET_SIZE);
#undef CONST

  printf("}\n");

  return 0;
}
