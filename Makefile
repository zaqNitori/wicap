CC=mipsel-openwrt-linux-gcc
PCAP_INC=~/openwrt/build_dir/target-mipsel_24kc_musl/libpcap-1.9.1/
PCAP_LIB=~/openwrt/build_dir/target-mipsel_24kc_musl/libpcap-1.9.1/
header=none
target=wicap
ext=
des_ip=none
des_path=~/workspace/

all: radiotap.o fc_hdr.o
        rm -rf $(target)$(ext)
        $(CC) $(target).c -I $(PCAP_INC) -L $(PCAP_LIB) -lpcap -o $(target)$(ext) radiotap.o fc_hdr.o

fc_hdr.o: fc_hdr.o
        $(CC) -c fc_hdr.c

radiotap.o: radiotap.c radiotap.h radiotap_iter.h platform.h
        $(CC) -c radiotap.c

clean:
        rm -rf $(target)$(ext)

send:
        scp $(target)$(ext) root@$(des_ip):$(des_path)