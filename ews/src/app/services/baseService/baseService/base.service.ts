import {
  HttpClient,
  HttpResponse,
  HttpResponseBase,
} from '@angular/common/http';
import { Observable, of, throwError } from 'rxjs';
import { catchError, map } from 'rxjs/operators';
import { ServerEnum, ServerPort } from './base.model';

export class BaseService<T> {
  /**
   * Make HTTP client available to child classes
   */
  baseurl = '';
  server_port = '';
  constructor(private url, private server: ServerEnum = ServerEnum.GOTHAM_DB, private http: HttpClient) {
    this.baseurl = this.url;
    this.server_port = "8080"
  }

  public get(className: new (data: any) => T, getUrl?: string) {
    const url = this.getFinalUrl(getUrl);
    return this.http.get(url).pipe(
      map((res) => {
        let obj = new className(res as T);
        return obj;
      }),
      catchError((error) => {
        throw throwError(() => error);
      })
    );
  }

  public post(className: new (data: T) => T, data: any, postUrl?: string) {
    let url = this.getFinalUrl(postUrl);
    console.log(url);
    // url = url.endsWith('/') ? url : url + '/';
    return this.http.post(url, data).pipe(
      map((res) => {
        let obj = new className(res as T);
        return obj;
      }),
      catchError((error) => {
        console.log(error);
        throw throwError(() => error);
      })
    );
  }

  getFinalUrl(urlExtended = ''): string {
    return this.gethost() + this.baseurl + urlExtended;
  }

  gethost() {
    return 'http://' + window.location.hostname + ':' + this.server_port;
  }
}
