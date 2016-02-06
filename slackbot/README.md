# Slack Bot

My personal slack bot. :boat:
It is distributed under MIT License.

## Build and run

```sh
# Clone third-party libraries
git clone --depth=1 https://github.com/miloyip/rapidjson rapidjson

# Setup build tool
make -C ../nori bootstrap

# Build
make xcode

# Run
./bin/slackbot -help
```

## Thanks

- RapidJSON
