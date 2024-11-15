import { Injectable } from "@angular/core";
import { BaseService } from "../../../baseService";
import { HttpClient } from "@angular/common/http";
import { LoginModel, LoginRequestModel } from "./loginService.model"
import { ServerEnum } from "@services/baseService";



const URL = '/auth/login'
@Injectable({
    providedIn: 'root'
})
export class LoginService extends BaseService<LoginModel | LoginRequestModel>{
    constructor(http:HttpClient){
        super(URL, ServerEnum.HULKBUSTER, http);
    }
}
