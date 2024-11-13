import { ButtonModel, ButtonTypeEnum } from '@patterns/button';
import { StringIds } from 'src/stringIds';

export enum FooterTypeEnum {
  APPLY_CANCEL = 'apply_cancel',
  YES_NO = 'yes_no',
  CUSTOM = 'custom',
}

export class FooterModel {
  footerType: FooterTypeEnum;
  id: string;
  event: any;
  buttons: ButtonModel[];

  /**
   *
   * @param footerType
   * @param id
   * @param buttons
   * @param event
   */
  constructor(
    footerType: FooterTypeEnum,
    id: string,
    buttons?: ButtonModel[],
    event?: any
  ) {
    this.footerType = footerType;
    this.id = id;
    this.event = event ?? null;
    let button: ButtonModel;
    switch (footerType) {
      case FooterTypeEnum.APPLY_CANCEL:
        this.buttons = [];
        button = new ButtonModel();
        button.setButtonValues(
          StringIds.cCANCEL,
          ButtonTypeEnum.SECONDRARY,
          id + '-cancel-button'
        );
        this.buttons.push(button);
        button = new ButtonModel();
        button.setButtonValues(
          StringIds.cAPPLY,
          ButtonTypeEnum.PRIMARY,
          id + '-apply-button'
        );
        this.buttons.push(button);
        break;
      case FooterTypeEnum.YES_NO:
        this.buttons = [];
        button = new ButtonModel();
        button.setButtonValues(
          StringIds.cNO,
          ButtonTypeEnum.SECONDRARY,
          id + '-no-button'
        );
        this.buttons.push(button);
        button = new ButtonModel();
        button.setButtonValues(
          StringIds.cYES,
          ButtonTypeEnum.PRIMARY,
          id + '-yes-button'
        );
        this.buttons.push(button);
        break;
      case FooterTypeEnum.CUSTOM:
        this.buttons = buttons?  buttons.slice(0, 2) : null;
        break;
      default:
        break;
    }
  }
}
