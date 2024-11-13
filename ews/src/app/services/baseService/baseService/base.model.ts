import { map, Observable } from 'rxjs';
import { HttpHeaders } from '@angular/common/http';

/**
 * Max number of http failed requests prior to returning a fatal error
 */
export const MAX_HTTP_RETRY = 3;

/**
 *  Max number of failed http request to consider that the connection to the printer is lost.
 */

export const MAX_HTTP_REQUEST_FAILURES = 10;

/**
 *  HTTP Timeout of 1.5 min.
 */
export const HTTP_REQUEST_TIMEOUT = 90000; // 1.5min http request timeout

/**
 * Default HTTP options for most requests (except for GET)
 * Content-Type is used to so our HTTP library expects JSON from CDM.
 * 'observe: response' is used to get the full HttpResponse
 */
const HTTP_DEFAULT_OPTIONS = {
    headers: new HttpHeaders({
        'Content-Type': 'application/json'
    }),
    observe: 'response' as 'response'
};
/**
 * Multipart HTTP options for most requests (for POST)
 * Content-Type is used to so our HTTP library expects Multipart from CDM.
 * 'observe: response' is used to get the full HttpResponse
 */
const HTTP_MULTIPART_OPTIONS = {
    headers: new HttpHeaders({
        'Content-Type': 'application/octet-stream'
    }),
    observe: 'response' as 'response'
};

/**
 * Http options for normal GET requests
 * The If-None_Match header is used to make sure CDM requests are not cached by the browser.  It is set to
 * the empty string so it won't match any ETags generated in the CDM response headers.
 */
const HTTP_GET_OPTIONS = {
    headers: new HttpHeaders({
        'If-None-Match': ''
    })
};

/**
 * Http options for GET request that require the full HttpResponse
 */
const HTTP_GET_RESPONSE_OPTIONS = {
    headers: HTTP_GET_OPTIONS.headers,
    observe: 'response' as 'response'
};

/**
 * HTTP options for the different request types
 */
export const HTTP_OPTIONS = {
    GET: HTTP_GET_OPTIONS,  // Returns just the response body
    GET_RESPONSE: HTTP_GET_RESPONSE_OPTIONS,  // Returns the full HttpResponse
    DELETE: HTTP_DEFAULT_OPTIONS,
    POST: HTTP_DEFAULT_OPTIONS,
    PUT: HTTP_DEFAULT_OPTIONS,
    PATCH: HTTP_DEFAULT_OPTIONS,
    POST_MULTIPART: HTTP_MULTIPART_OPTIONS
};

/**
 * Enum type that specifies the possible HTTP request types
 */
export enum HttpRequestEnum {
    GET = 'GET',
    POST = 'POST',
    PUT = 'PUT',
    DELETE = 'DELETE'
}

/**
 * Enum type that specifies the ServerEnum
 */
export enum ServerEnum {
    HULKBUSTER = "HULKBUSTER",
    GOTHAM_DB = "GOTHAM_DB",
    PAPER = 'PAPER'
}

/**
 * Enum type that specifies the ServerPort
 */
export enum ServerPort {
    "HULKBUSTER" = "8001",
    "GOTHAM_DB" = "8000",
    "PAPER" = '8002'
}

/**
 * Enum type that specifies the possible HTTP status code response values
 * Response status codes
 */
export enum HttpResponseStatusCodeCategoryEnum {
    UNKNOWN = 0,  // When browser detects an error (like net::ERR_NETWORK_UNREACHABLE), status is 0
    CONTINUE = 100,
    SUCCESSFUL = 200,
    MULTIPLE_CHOICES = 300,
    BAD_REQUEST = 400,
    CONFLICT = 409,
    INTERNAL_SERVER_ERROR = 500
}

/**
 * String literal type that specifies the possible HTTP status codes provided by the browser, but not defined as
 * a HTTP response
 */
export type HttpBrowserErrorStatusCodeType = -1;

/**
 * Browser Error codes
 */
export enum HttpBrowserErrorStatusCodeEnum {
    BROWSER_ERROR_STATUS_CODES_ERROR = -1
}

/**
 * Enum type that specifies the possible HTTP status codes of the 1XX responses category (Information responses)
 * Continue Status codes
 */
export enum HttpContinueStatusCodesEnum {
    CONTINUE = 100,
    SWITCHING_PROTOCOLS = 101,
    PROCESSING = 102,
    CHECKPOINT = 103
}

/**
 * Enum type that specifies the possible HTTP status codes of the 2XX responses category (Successful responses)
 * Successful status codes
 */
export enum HttpSuccessfulStatusCodesEnum {
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NON_AUTHORITATIVE_INFORMATION = 203,
    NO_CONTENT = 204,
    RESET_CONTENT = 205,
    PARTIAL_CONTENT = 206,
    MULTI_STATUS = 207,
    ALREADY_REPORTED = 208,
    IM_USED = 226
}

/**
 * Enum type that specifies the possible HTTP status codes of the 3XX responses category (Redirection messages)
 * Redirection status codes
 */
export enum HttpResponseMultipleChoicesEnum {
    MULTIPLE_CHOICE = 300,
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    SEE_OTHER = 303,
    NOT_MODIFIED = 304,
    TEMPORARY_REDIRECT = 307,
    PERMANENT_REDIRECT = 308
}

/**
 *  Enum that specifies the possible HTTP status codes of the 4XX responses category (Client error responses)
 *  Client Error status codes
 */
export enum HttpClientErrorStatusCodesEnum {
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    NOT_ACCEPTABLE = 406,
    PROXY_AUTHENTICATION_REQUIRED = 407,
    REQUEST_TIMEOUT = 408,
    CONFLICT = 409,
    GONE = 410,
    URI_TOO_LONG = 414,
    UNSUPPORTED_MEDIA_TYPE = 415,
    REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    EXPECTATION_FAILED = 417,
    IM_A_TEAPOT = 418,
    MISDIRECTED_REQUEST = 421,
    UNPROCESSABLE_ENTITY = 422,
    LOCKED = 423,
    FAILED_DEPENDENCY = 424,
    UPGRADE_REQUIRED = 426,
    PRECONDITION_REQUIRED = 429,
    REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
    UNAVAILABLE_FOR_LEGAL_REASONSE = 451
}

/**
 * Enum that specifies the possible HTTP status codes of the 5XX responses category (Server error responses)
 * Server Error status codes
 */
export enum HttpServerErrorStatusCodesEnum {
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIMEOUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505,
    VARIANT_ALSO_NEGOTIATES = 506,
    INSUFFICIENT_STORAGE = 507,
    LOOP_DETECTED = 508,
    NOT_EXTENDED = 510,
    NETWORK_AUTHENTICATION_REQUIRED = 511,
    NOT_UPDATED = 512
}

/**
 * HTTP Headers Type enum to string
 */
export enum HttpHeaderNameEnum {
    LOCATION = 'Location',
    CONTENT_TYPE = 'Content-Type',
    CONTENT_DISPOSITION = 'Content-Disposition',
}

/**
 * HttpUtils class, contains useful method to handle http response codes
 */
export class HttpUtils {

    /**
     * Gets the status code of the promise response
     * @param response - Promise response
     * @returns Status code of the response
     */
    public static getResponseStatusCode(response: Observable<any>): number {
        const statusCode: number =response['status'] as number;
            return statusCode;
    }

    /**
     * Gets the response status category from the response status code (1xx - 2xx - 3xx - 4xx - 5xx)
     * @param statusCode - Status code
     * @returns Enum value of the category that contains the status code
     */
    public static getResponseStatusCodeCategory(statusCode: number): HttpResponseStatusCodeCategoryEnum {
            if (statusCode >= HttpResponseStatusCodeCategoryEnum.INTERNAL_SERVER_ERROR) {
                return HttpResponseStatusCodeCategoryEnum.INTERNAL_SERVER_ERROR;
            } else if (statusCode >= HttpResponseStatusCodeCategoryEnum.BAD_REQUEST) {
                return HttpResponseStatusCodeCategoryEnum.BAD_REQUEST;
            } else if (statusCode >= HttpResponseStatusCodeCategoryEnum.MULTIPLE_CHOICES) {
                return HttpResponseStatusCodeCategoryEnum.MULTIPLE_CHOICES;
            } else if (statusCode >= HttpResponseStatusCodeCategoryEnum.SUCCESSFUL) {
                return HttpResponseStatusCodeCategoryEnum.SUCCESSFUL;
            } else if (statusCode >= HttpResponseStatusCodeCategoryEnum.CONTINUE) {
                return HttpResponseStatusCodeCategoryEnum.CONTINUE;
            } else {
                return HttpResponseStatusCodeCategoryEnum.UNKNOWN;
            }
    }

    /**
     * Checks if the response is defined, with success status code and with data defined
     * @param response - Response
     * @returns true is response is defined, have 200 status and data defined, false otherwise
     */
    public static isResponseSuccessWithData(response: any): boolean {
        return HttpUtils.isResponseSuccess(response) &&response.data;
    }

    /**
     * Checks if the response is defined, with success status code but could have no data inside
     * @param response - Response
     * @returns true is response is defined, have 200 status, false otherwise
     */
    public static isResponseSuccess(response: any): boolean {
        const statusCodeCategory = HttpUtils.getResponseStatusCodeCategory(response?.status);
            return (statusCodeCategory === HttpResponseStatusCodeCategoryEnum.SUCCESSFUL);
    }

    /**
     * Checks if the protocol is http or https
     * @returns true if protocol is https, false otherwise
     */
    public static isProtocolHttps(): boolean {
        return (window.location.protocol === 'https:');
    }
}
