import { StringIdsType } from "src/stringIds";
import { LinkTarget } from "../common.model";

export enum ButtonTypeEnum {
  PRIMARY = 'primary',
  SECONDRARY = 'secondrary',
  DELETE = 'delete',
  WARNING = 'warning'
}

export class ButtonModel {
  text: StringIdsType;
  buttonType: ButtonTypeEnum;
  id: string;
  event: any;
  target: LinkTarget;
  link: StringIdsType;
  setButtonValues(
    text: StringIdsType,
    buttonType: ButtonTypeEnum,
    id: string,
    event?: any,
    target?: LinkTarget,
    link?: StringIdsType
  ) {
    this.text = text;
    this.buttonType = buttonType;
    this.id = id;
    this.event = event ?? null;
    this.target = target ?? LinkTarget.SELF;
    this.link = link ?? null;
  }
}
