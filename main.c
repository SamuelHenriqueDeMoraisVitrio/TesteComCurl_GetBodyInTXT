#include <curl/curl.h>

int main(int argc, char *argv[]) {
  CURL *curl;
  CURLcode *rest;

  FILE *arqTXT = fopen("texto/texto.txt", "w");

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, arqTXT);

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  fclose(arqTXT);

  return 0;
}
