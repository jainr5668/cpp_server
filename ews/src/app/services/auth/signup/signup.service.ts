import { Injectable } from "@angular/core";
import { BaseService } from "../../baseService";
import { HttpClient } from "@angular/common/http";
import { SignupModel, SignupRequestModel } from "./signup.model";
import { ServerEnum } from "@services/baseService/baseService/base.model";



const URL = '/auth/signup'
@Injectable({
    providedIn: 'root'
})
export class SignupService extends BaseService<SignupModel | SignupRequestModel>{
    constructor(http:HttpClient){
        super(URL, ServerEnum.HULKBUSTER, http);
    }
}
