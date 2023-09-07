# Patch freeradius to allow for a larger MAX_PASS_LEN in order to support Aruba MPSK encryption
# which encodes more data into the password encryption than the standard specifies

--- src/lib/radius.c.orig	2023-07-11 15:51:02
+++ src/lib/radius.c	2023-07-11 15:52:49
@@ -533,7 +533,7 @@
 	fr_md5_destroy(&context);
 }
 
-#define MAX_PASS_LEN (128)
+#define MAX_PASS_LEN (256)
 static void make_passwd(uint8_t *output, ssize_t *outlen,
 			uint8_t const *input, size_t inlen,
 			char const *secret, uint8_t const *vector)
@@ -4638,7 +4638,7 @@
 	 *	The buffer we're putting it into above is 254, so
 	 *	we don't need to do any length checking.
 	 */
-	if (pwlen > 128) pwlen = 128;
+	if (pwlen > 254) pwlen = 254;
 
 	/*
 	 *	Catch idiots.
