# Patch squid 4.0.x to not require that the two ECN bits of the ToS byte be set
# to zero, as this effectively limits us to 63 usable unique ToS bytes instead
# of 255.
#
--- src/cache_cf.cc.orig        2017-11-14 13:38:35.000000000 -0700
+++ src/cache_cf.cc     2017-11-14 13:39:04.000000000 -0700
@@ -1480,12 +1480,6 @@
         return;
     }

-    const unsigned int chTos = tos & 0xFC;
-    if (chTos != tos) {
-        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: Tos value '" << tos << "' adjusted to '" << chTos << "'");
-        tos = chTos;
-    }
-
     acl_tos *l = new acl_tos;

     l->tos = (tos_t)tos;
