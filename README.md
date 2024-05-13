# DuckDNS Client
DuckDnsClient is a lightweight executable made to update [DuckDNS](https://www.duckdns.org/) DDNS hostnames.
It tries to update DDNS automatically and accepts force update requests.

### Dependencies
* [libfmt](https://github.com/fmtlib/fmt)
* [libcurl](https://github.com/curl/curl)
* [libspdlog](https://github.com/gabime/spdlog)

### Compilation
```
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j
```

### Installation
It's up to you how you install the client.
It needs to run continuously and to have configuration file `/etc/duckdnsclient.conf`.
For example, `DuckDnsClient` can be put in `/usr/local/bin` and `systemctl` service `/etc/systemd/system/duckdnsclient.service` can be created.
Don't forget to generate configuration file with `./DuckDnsClient --generate`.

## DDNS update methods
### Automatic update
Client tries to update DDNS every first second of every hour, so it's 24 requests a day.
It is made the way that it can be calculated anywhere in the world when next update happens and DuckDNS servers are not attacked too often.
If you are in a remote location and it's 09:42, it is guaranteed that the client in your local network will update DDNS in 18 minutes.

### Force update
Linux's `SIGUSR1` signal can be sent to the executable to trigger force update. This is useful when you have physical access to the computer and it is known that WAN IP changed.
For example, you may execute this command after you change configuration of your router and it reboots:
```
$ kill -s SIGUSER1 $(pidof DuckDnsClient)
```

## Configuration
Client's configuration file is `/etc/duckdnsclient.conf`.
Update token and hosts are configured there.
Can be created using:
```
$ ./DuckDnsClient --generate
```

## Example files
Example files, such as `systemctl` service and force update script, can be found in `files/` directory.
