package endpoints

import (
    "fmt"
    "net/http"
)

func init(){
    http.HandleFunc("/test", func(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Hello, %q", r.URL.Path)
        fmt.Println(r.URL.Path)
    })
}