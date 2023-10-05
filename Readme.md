# Wikiextract

The utility converts the source Wikipedia text into pair of files:

* `links.tsv`
 * `doc id` - the ID of the Wikipedia article
 * `first token id` - the ID of the first token of the link
 * `last token id` - the ID of the last token of the link
 * `link text` - the linked text form the Wikipedia article (the text visible to the user)
 * `link target` - the name of the Wikipedia article that is a target of the link
* `tokens.tsv` - Content of each Wikipedia article broken into tokens:
 * `doc id` - the ID of the Wikipedia article
 * `token id` - the id of the token within the article
 * `space` - 1 indicates that there was a white character before the token
 * `token` - the content of the token

These files are useful for computing statistics of the number of links appearing
in the text for a given expression, etc.


## Docker

The Docker compose file for this service is in SQL subproject.
The assumed directory structure is as follows:

```
cyclopedio/
    data/pl/data/
    data/pl/rod/
    sql/
    wikiextract/
```

The scripts might be run with Docker and `docker compose`. The `docker-compose` is in `sql` subproject.

```
docker compose up # in cyclopedio/sql
# in a separate window
docker exec cyclopedio-wikiextract bundle exec rake build
docker exec cyclopedio-wikiextract bundle exec rake tokens:extract
```
