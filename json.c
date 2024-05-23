#include "CxpathJson.h"

int main(int argc, char *argv[]) {
  CxpathJsonNamespace js = newCxpathJsonNamespace();
  CxpathJsonErrorNamespace errors = js.errors;

  CxpathJson *json = js.new_from_file("texto/texto.json");

  short userId = js.get_int(json, "[0, 'userId']");
  int id = js.get_int(json, "[0, 'id']");
  char *title = js.get_str(json, "[0, 'title']");
  char *body = js.get_str(json, "[0, 'body']");

  if (errors.has_errors(json)) {
    char *message = errors.get_error_message(json);
    int code = errors.get_error_code(json);
    printf("code: %d\n", code);
    printf("message: %s\n", message);
    js.free(json);
    return 1;
  }

  fprintf(stdout, "\n\tuserid\t%d\n\n\tid\t%d\n\n\ttitle\t%s\n\n\tbody\t%s\n\n\n", userId, id,
          title, body);
}
