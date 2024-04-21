while true; do
siege -c 10 -t 1M http://0.0.0.0:3007
siege -c 10 -t 1M http://0.0.0.0:3008
siege -c 10 -t 1M http://0.0.0.0:3009
done
