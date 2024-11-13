import { ContentModel } from "@patterns/content";
import { FooterModel } from "@patterns/footer";
import { StringIdsType } from "src/stringIds";

export class CardModel {
    id:StringIdsType;
    event:any;
    title: StringIdsType;
    footer: FooterModel;
    contents: ContentModel[] = [];
    
    setCardValues(id:StringIdsType, event:any, title?:StringIdsType, footer?:FooterModel){
        this.id = id;
        this.event = event ?? null;
        this.footer = footer ?? null;
        this.title = title ?? null;
    }
}