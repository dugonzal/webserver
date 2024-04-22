while true; do
siege -c 10 -t 1M http://127.0.0.1:3007;
siege -c 10 -t 1M http://127.0.0.1:3008;
siege -c 10 -t 1M http://127.0.0.1:3009;
done
curl  --http2 http://0.0.0.0:3009
