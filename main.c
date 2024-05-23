#include <curl/curl.h>

int main(int argc, char *argv[]) {
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com");
    FILE *arqTXT = fopen("texto/main.html", "w");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, arqTXT);

    res = curl_easy_perform(curl);
    fclose(arqTXT);

    if (res != CURLE_OK) {
      char *INFOCURL = NULL;
      curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &INFOCURL);
      fprintf(stderr, "\n\tErro ao executar sessão %s:\n\t%s\n", INFOCURL, curl_easy_strerror(res));
      return 1;
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return 0;
}
