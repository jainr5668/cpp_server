import { StringIdsType } from "src/stringIds";

export enum ElementType{
    SELECT = 'select',
    TEXT = 'text',
    PASSWORD = 'password',
    TOGGLE = 'toggle',
    EMAIL = 'email',
    FILE = 'file',
    NUMBER = 'number'

}
export class SelectOption{
    value: string;
    label: StringIdsType;
    disabled: boolean;
    constructor(value: string, label:StringIdsType, disabled?:boolean){
        this.label = label;
        this.value = value;
        this.disabled = disabled;
    }
}
export class ElementModel {
  id: string;
  event: any;
  type: ElementType;
  label: StringIdsType;
  options: SelectOption[];
  model: any;
  property: string;
  visible: boolean;
  disabled: boolean;
  placeholder: string;
  required: boolean;
  colspan: number;

  private commonProperty(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event: any,
    colspan: number
  ) {
    this.id = id;
    this.label = label;
    this.model = model;
    this.property = property;
    this.event = event ?? null;
    this.colspan = colspan ?? 1;
  }

  select(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    options: SelectOption[],
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event, colspan);
    this.type = ElementType.SELECT;
    this.options = options;
  }

  textField(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event, colspan);
    this.type = ElementType.TEXT;
  }

  numberField(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event, colspan);
    this.type = ElementType.NUMBER;
  }

  passwordField(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event, colspan);
    this.type = ElementType.PASSWORD;
  }

  toggle(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event, colspan);
    this.type = ElementType.TOGGLE;
  }
  email(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event,colspan);
    this.type = ElementType.EMAIL;
  }

  file(
    id: string,
    label: StringIdsType,
    model: any,
    property: string,
    event?: any,
    colspan?: number
  ) {
    this.commonProperty(id, label, model, property, event,colspan);
    this.type = ElementType.FILE;
  }
  
}