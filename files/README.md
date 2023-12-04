# Example files

## ddns-update.sh
A simple script that forces system's running `DuckDnsClient` to update DDNS.
May be installed anywhere, for example in `/usr/local/etc`.
If that directory is in `PATH`, force update can be done by executing:
```
$ ddns-update.sh
```

## duckdnsclient.service
A `systemctl` example service that can be used to manage the executable.
Should be installed in `/etc/systemd/system` and configured:
```
$ systemctl daemon-reload
$ systemctl start duckdnsclient
$ systemctl enable duckdnsclient
```
The `enable` command makes `systemctl` launch `DuckDnsClient` on every startup of the system.
`DuckDnsClient`'s logs can be checked by using:
```
$ systemctl status duckdnsclient
```
