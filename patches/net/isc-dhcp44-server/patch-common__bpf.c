# A faster get_hw_addr that does not use getifaddrs()
# getifaddrs() is iterated n^2 times the number of interfaces (VLANs) and/or
# addresses
--- common/bpf.c.orig
+++ common/bpf.c
@@ -57,6 +57,9 @@
 #if defined(USE_BPF_SEND) || defined(USE_BPF_RECEIVE) || defined(USE_BPF_HWADDR)
 #include <net/if_types.h>
 #include <ifaddrs.h>
+#ifdef __FreeBSD__
+#include <sys/sysctl.h>
+#endif
 #endif
 
 #include <errno.h>
@@ -599,6 +602,71 @@ void maybe_setup_fallback ()
 #endif
 
 #if defined(USE_BPF_RECEIVE) || defined(USE_BPF_HWADDR)
+#ifdef __FreeBSD__
+/* NET_RT_IFLIST sysctl() with an ifindex is substantially faster than
+	iterating getifaddrs() with thousands of interfaces and/or addresses */
+void
+get_hw_addr(const char *name, struct hardware *hw) {
+	struct if_msghdr *ifm;
+	struct sockaddr_dl *sa;
+	unsigned int ifindex;
+	u_char *buf;
+	size_t len;
+
+	ifindex = if_nametoindex(name);
+
+	int mib[] = { CTL_NET, AF_ROUTE, 0, AF_LINK, NET_RT_IFLIST, ifindex };
+
+	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
+		log_fatal("Error getting interface information; %m");
+	if ((buf = malloc(len)) == NULL)
+		log_fatal("Error getting interface information; %m");
+	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
+		free(buf);
+		log_fatal("Error getting interface information; %m");
+	}
+	ifm = (struct if_msghdr *)buf;
+	sa = (struct sockaddr_dl *)(ifm + 1);
+
+	if (sa == NULL) {
+		log_fatal("No interface called '%s'", name);
+	}
+
+	/*
+	 * Pull out the appropriate information.
+	 */
+        switch (sa->sdl_type) {
+                case IFT_ETHER:
+#if defined (IFT_L2VLAN)
+		case IFT_L2VLAN:
+#endif
+                        hw->hlen = sa->sdl_alen + 1;
+                        hw->hbuf[0] = HTYPE_ETHER;
+                        memcpy(&hw->hbuf[1], LLADDR(sa), sa->sdl_alen);
+                        break;
+		case IFT_ISO88023:
+		case IFT_ISO88024: /* "token ring" */
+		case IFT_ISO88025:
+		case IFT_ISO88026:
+                        hw->hlen = sa->sdl_alen + 1;
+                        hw->hbuf[0] = HTYPE_IEEE802;
+                        memcpy(&hw->hbuf[1], LLADDR(sa), sa->sdl_alen);
+                        break;
+#ifdef IFT_FDDI
+                case IFT_FDDI:
+                        hw->hlen = sa->sdl_alen + 1;
+                        hw->hbuf[0] = HTYPE_FDDI;
+                        memcpy(&hw->hbuf[1], LLADDR(sa), sa->sdl_alen);
+                        break;
+#endif /* IFT_FDDI */
+                default:
+                        log_fatal("Unsupported device type %d for \"%s\"",
+                                  sa->sdl_type, name);
+        }
+
+	free(buf);
+}
+#else
 void
 get_hw_addr(const char *name, struct hardware *hw) {
 	struct ifaddrs *ifa;
@@ -657,4 +725,5 @@ get_hw_addr(const char *name, struct hardware *hw) {
 
 	freeifaddrs(ifa);
 }
-#endif
+# endif
+# endif

