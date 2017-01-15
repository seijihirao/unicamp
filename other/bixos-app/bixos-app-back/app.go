package main

import (
    _ "./endpoints"
    "log"
    "net/http"
)

func main(){
    err := http.ListenAndServe(":8080", nil)
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}