import { ElementModel } from "@patterns/element";
import { StringIds, StringIdsType } from "src/stringIds";

export class ContentModel {
    id:string;
    title: StringIdsType;
    description: StringIdsType[]; 
    event:any;
    elements:ElementModel[]
    cols: number;
    
    setContentValues(id:string, title?:StringIdsType, description?:StringIdsType[], event?:any){
        this.id = id;
        this.title = title;
        this.event = event ?? null;
        this.description = description ?? null;
    }
}