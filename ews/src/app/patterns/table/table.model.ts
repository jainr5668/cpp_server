import { ButtonModel } from "@patterns/button";
import { StringIds } from "src/stringIds";

export class TableColumnModel {
    id: string;
    title: StringIds;
    key: string;

    constructor(id: string, title: StringIds, key: string) {
        this.id = id;
        this.title = title;
        this.key = key;
    }
}

export enum TableElementType {
    TEXT = 'text',
    BUTTON = 'button',
    ICON = 'icon',
    CHECKBOX = 'checkbox',
    ELEMENT = 'element',
}

export class TableDataModel {
    id: string;
    key: string;
    data: any;
    type: TableElementType;
    event: any;

    constructor(id: string, key:string, data: any, type: TableElementType, event?: any) {
        this.id = id;
        this.key = key;
        this.data = data;
        this.type = type;
        this.event = event ?? null;
    }
}
export class TableRowModel{
    data: TableDataModel[];
    constructor(data?: TableDataModel[]){
        this.data = data;
    }
}

export class TableModel {
    id: string;
    event: any;
    columns: TableColumnModel[];
    rows: TableRowModel[];
    actionButtons: ButtonModel[];
    setTableValues(id: string, columns: TableColumnModel[], rows: TableDataModel[], event?: any) {
        this.id = id;
        this.columns = columns;
        this.rows = rows;
        this.event = event ?? null;
    }
}