#include <curl/curl.h>

#include "CxpathJson.h"

CxpathJsonNamespace js;
CxpathJsonErrorNamespace errors;

size_t lendo_ids(CxpathJson *json, size_t size, size_t num_size, FILE *arqTXT) {
  if (errors.has_errors(json)) {
    char *message = errors.get_error_message(json);
    int code = errors.get_error_code(json);
    printf("code: %d\n", code);
    printf("message: %s\n", message);
    js.free(json);
    fprintf(stderr, "Erro\n");
  }  // if errors

  for (size_t i = 0; i < js.size(json, "[]"); i++) {
    int id = js.get_int(json, "[%d, 'id']", i);
    if (errors.has_errors(json)) {
      char *message = errors.get_error_message(json);
      int code = errors.get_error_code(json);
      printf("code: %d\n", code);
      printf("message: %s\n", message);
      js.free(json);
      fprintf(stderr, "Erro\n");
    }  // if errors
    fprintf(arqTXT, "%d\n", id);

  }  // for json

  js.free(json);

  return size * num_size;
}  // function

int main(int argc, char *argv[]) {
  js = newCxpathJsonNamespace();
  errors = js.errors;

  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, lendo_ids);

    FILE *arqTXT = fopen("texto/texto.txt", "wb");

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
