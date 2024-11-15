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

  public post(className: new (data: T) => T, data: T, postUrl?: string) {
    let url = this.getFinalUrl(postUrl);
    console.log(url);
    // url = url.endsWith('/') ? url : url + '/';
    return this.http.post(url, data).pipe(
      map((res) => {
        console.log(res);
        let obj = <T>res;
        console.log(obj);
        return obj;
      }),
      catchError((error) => {
        console.log(error);
        throw throwError(() => error);
      })
    );
  }

  public delete(className: new (data: T) => T, deleteUrl?: string) {
    let url = this.getFinalUrl(deleteUrl);
    return this.http.delete(url).pipe(
      map((res) => {
        return res;
      }),
      catchError((error) => {
        throw throwError(() => error);
      })
    );
  }

  public put(className: new (data: T) => T, data: T, putUrl?: string) {
    let url = this.getFinalUrl(putUrl);
    return this.http.put(url, data).pipe(
      map((res) => {
        let obj = <T>res;
        return obj;
      }),
      catchError((error) => {
        throw throwError(() => error);
      })
    );
  }

  public patch(className: new (data: T) => T, data: T, patchUrl?: string) {
    let url = this.getFinalUrl(patchUrl);
    return this.http.patch(url, data).pipe(
      map((res) => {
        let obj = <T>res;
        return obj;
      }),
      catchError((error) => {
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
