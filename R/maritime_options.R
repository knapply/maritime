#' `{maritime}` Options
#' 
#' @template author-bk
#' 
#' @examples 
#' maritime_options()
#' 
#' @export
maritime_options <- function() {
    opts <- c("maritime_parse",
              "maritime_as_df",
              "maritime_as_sf",
              "maritime_add_query_cols",
              "maritime_query_col_prefix",
              "maritime_as_tibble",
              "maritime_snakecase_col_names",
              "maritime_return_raw_response",
              "maritime_verbose")
    data.frame(
        option = opts,
        value = eval(parse(text = paste0(opts, "()"))),
        stringsAsFactors = FALSE
    )
}



#' @rdname maritime_options
#' @export
maritime_parse <- function() {
    getOption("maritime_parse", TRUE)
}


#' @rdname maritime_options
#' @export
maritime_as_df <- function() {
    getOption("maritime_as_df", TRUE)
}


#' @rdname maritime_options
#' @export
maritime_as_sf <- function() {
    getOption("maritime_as_sf", FALSE)
}


#' @rdname maritime_options
#' @export
maritime_as_tibble <- function() {
    getOption("maritime_as_tibble", TRUE)
}


#' @rdname maritime_options
#' @export
maritime_add_query_cols <- function() {
    getOption("maritime_add_query_cols", TRUE)
}


#' @rdname maritime_options
#' @export
maritime_query_col_prefix <- function() {
    getOption("maritime_query_col_prefix", "query_")
}


#' @rdname maritime_options
#' @export
maritime_snakecase_col_names <- function() {
    getOption("maritime_snakecase_col_names", TRUE)
}


#' @rdname maritime_options
#' @export
maritime_return_raw_response <- function() {
    getOption("maritime_return_raw_response", FALSE)
}

#' @rdname maritime_options
#' @export
maritime_verbose <- function() {
    getOption("maritime_verbose", TRUE)
}
