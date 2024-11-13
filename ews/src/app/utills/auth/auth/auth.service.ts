import { Subject } from 'rxjs';
import {AuthModel} from './auth.model'

export class AuthService{
    public static isAuthenticatedSubject: Subject<boolean> = new Subject<boolean>()
    constructor(){}
    tokenKey = 'token';

    isAuthenticated(){
        if (!this.is_token_expired(this.getToken())){
            return true;
        } else {
            return false;
        }
    }

    setToken(token:string){
        localStorage.setItem(this.tokenKey, token);
        AuthService.isAuthenticatedSubject.next(true);
    }

    getToken(){
        return localStorage.getItem(this.tokenKey);
    }

    removeToken(){
        localStorage.removeItem(this.tokenKey);
        AuthService.isAuthenticatedSubject.next(false);
    }

    is_token_expired(token:string){
        if (token == null){
            return true;
        }
        token = token.split('.')[1];
        token = JSON.parse(atob(token));
        console.log("token_data:::", token);
        if (token['exp'] > Date.now() / 1000){
            return false;
        } else {
            return true;
        }
    }
}
