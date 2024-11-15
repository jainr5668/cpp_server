import { Injectable } from "@angular/core";
import { BaseService } from "../baseService";
import { HttpClient } from "@angular/common/http";
import { GetTodoModel, GetTodosModel, TodosModel } from "./todos.model";
import { ServerEnum } from "@services/baseService/baseService/base.model";



const URL = '/todos';
@Injectable({
    providedIn: 'root'
})
export class TodosService extends BaseService<TodosModel | GetTodoModel | GetTodosModel>{
    constructor(http:HttpClient){
        super(URL, ServerEnum.HULKBUSTER, http);
    }
}
