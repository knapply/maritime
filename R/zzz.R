.build_msgs <- function() {
    ais_msg_strings <- c(
        "msg_1_2_3",
        "msg_4_11",
        "msg_5",
        "msg_6",
        "msg_7_13",
        "msg_8",
        "msg_9",
        "msg_10",
        "msg_11",
        "msg_12",
        "msg_14",
        "msg_15",
        "msg_16",
        "msg_17",
        "msg_18",
        "msg_19",
        "msg_20",
        "msg_21",
        "msg_22",
        "msg_23",
        "msg_24",
        "msg_25",
        "msg_26",
        "msg_27"
    )
    structure(
        mapply(
            function(.x, .y) {
                structure(.x, class = "ais_msg", msg = .y)
            },
            seq_along(ais_msg_strings), ais_msg_strings,
            SIMPLIFY = FALSE, USE.NAMES = FALSE
        ),
        names = ais_msg_strings,
        class = "ais_msgs"
    )
}

#' @export
print.ais_msg <- function(x, ...) {
    out <- strsplit(attr(x, "msg"), "_")[[1L]][-1L]
    cat("msgs:", paste(out, collapse = ", "))
}

#' @export
print.ais_msgs <- function(x, ...) {
    cat("ais_msgs\n")
}


#' @name ais_msgs
#' @title ais_msgs
#' 
#' @export
ais_msgs <- .build_msgs()

.onLoad <- function(libname, pkgname) {
    invisible()
}

