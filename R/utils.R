# .is_chr <- function(x, ...) .is_template(x, is.character, ...)
# .is_int <- function(x, ...) .is_template(x, is.integer, ...)
# .is_dbl <- function(x, ...) .is_template(x, is.double, ...)
# .is_num <- function(x, ...) .is_template(x, is.numeric, ...)
# .is_lgl <- function(x, ...) .is_template(x, is.logical, ...)
# 
# .is_scalar <- function(x, na_rm = TRUE) {
#     if (!is.atomic(x)) return(FALSE)
#     
#     if (na_rm) length(x[!is.na(x)]) == 1L else length(x) == 1L
# }
# 
# .is_scalar_chr <- function(x, ...) .is_scalar(x, ...) && is.character(x)
# .is_scalar_dbl <- function(x, ...) .is_scalar(x, ...) && is.double(x)
# .is_scalar_num <- function(x, ...) .is_scalar(x, ...) && is.numeric(x)
# .is_scalar_int <- function(x, ...) .is_scalar(x, ...) && is.integer(x)
# .is_scalar_lgl <- function(x, ...) .is_scalar(x, ...) && is.logical(x)
# .is_scalar_intish <- function(x, ...) .is_scalar(x, ...) && .is_intish(x)
