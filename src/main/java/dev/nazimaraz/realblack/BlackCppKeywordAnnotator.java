package dev.nazimaraz.realblack;

import com.intellij.lang.annotation.AnnotationHolder;
import com.intellij.lang.annotation.Annotator;
import com.intellij.lang.annotation.HighlightSeverity;
import com.intellij.openapi.editor.colors.TextAttributesKey;
import com.intellij.psi.PsiComment;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiWhiteSpace;
import com.intellij.psi.util.PsiTreeUtil;
import org.jetbrains.annotations.NotNull;

import java.util.Set;

public final class BlackCppKeywordAnnotator implements Annotator {
    private static final TextAttributesKey NAMESPACE_KEYWORD =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.KEYWORD.NAMESPACE");
    private static final TextAttributesKey AUTO_KEYWORD =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.KEYWORD.AUTO");
    private static final TextAttributesKey CONST_KEYWORD =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.KEYWORD.CONST");
    private static final TextAttributesKey CONSTEXPR_KEYWORD =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.KEYWORD.CONSTEXPR");
    private static final TextAttributesKey TYPE_KEYWORD =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.KEYWORD.TYPE");
    private static final TextAttributesKey TEMPLATE_KEYWORD =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.KEYWORD.TEMPLATE");
    private static final TextAttributesKey OWNER_TYPE =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.OWNER_TYPE");
    private static final TextAttributesKey CALLABLE_NAME =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.CALLABLE_NAME");
    private static final TextAttributesKey TRAILING_RETURN_TYPE =
            TextAttributesKey.createTextAttributesKey("BLACK.CPP.TRAILING_RETURN_TYPE");

    private static final Set<String> TYPE_KEYWORDS = Set.of(
            "bool", "char", "char8_t", "char16_t", "char32_t", "double", "float",
            "int", "long", "short", "signed", "unsigned", "void", "wchar_t",
            "class", "struct", "enum", "union", "typedef", "using"
    );

    @Override
    public void annotate(@NotNull PsiElement element, @NotNull AnnotationHolder holder) {
        if (element.getFirstChild() != null) {
            return;
        }

        int length = element.getTextLength();
        if (length == 0 || length > 64) {
            return;
        }

        TextAttributesKey key = keyFor(element);
        if (key == null) {
            return;
        }

        holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                .range(element)
                .textAttributes(key)
                .create();
    }

    private static TextAttributesKey keyFor(PsiElement element) {
        String text = element.getText();

        if (isIdentifier(text)) {
            if (isAfterTrailingArrow(element)) {
                return TRAILING_RETURN_TYPE;
            }
            if (isBeforeScopeResolution(element)) {
                return OWNER_TYPE;
            }
            if (isBeforeCallParenthesis(element) && isAfterScopeResolution(element)) {
                return CALLABLE_NAME;
            }
        }

        switch (text) {
            case "namespace":
                return NAMESPACE_KEYWORD;
            case "auto":
                return AUTO_KEYWORD;
            case "void":
                return isAfterTrailingArrow(element) ? TRAILING_RETURN_TYPE : TYPE_KEYWORD;
            case "const":
                return CONST_KEYWORD;
            case "constexpr":
            case "consteval":
            case "constinit":
                return CONSTEXPR_KEYWORD;
            case "template":
            case "typename":
                return TEMPLATE_KEYWORD;
            default:
                return TYPE_KEYWORDS.contains(text) ? TYPE_KEYWORD : null;
        }
    }

    private static boolean isIdentifier(String text) {
        if (text.isEmpty()) {
            return false;
        }

        char first = text.charAt(0);
        if (!Character.isLetter(first) && first != '_') {
            return false;
        }

        for (int i = 1; i < text.length(); i++) {
            char c = text.charAt(i);
            if (!Character.isLetterOrDigit(c) && c != '_') {
                return false;
            }
        }

        return true;
    }

    private static boolean isBeforeCallParenthesis(PsiElement element) {
        PsiElement next = nextSignificantLeaf(element);
        return next != null && "(".equals(next.getText());
    }

    private static boolean isBeforeScopeResolution(PsiElement element) {
        PsiElement next = nextSignificantLeaf(element);
        if (next == null) {
            return false;
        }
        if ("::".equals(next.getText())) {
            return true;
        }
        return ":".equals(next.getText()) && hasNextText(next, ":");
    }

    private static boolean isAfterScopeResolution(PsiElement element) {
        PsiElement previous = previousSignificantLeaf(element);
        if (previous == null) {
            return false;
        }
        if ("::".equals(previous.getText())) {
            return true;
        }
        return ":".equals(previous.getText()) && hasPreviousText(previous, ":");
    }

    private static boolean isAfterTrailingArrow(PsiElement element) {
        PsiElement previous = previousSignificantLeaf(element);
        if (previous == null) {
            return false;
        }
        if ("->".equals(previous.getText())) {
            return true;
        }
        return ">".equals(previous.getText()) && hasPreviousText(previous, "-");
    }

    private static boolean hasNextText(PsiElement element, String text) {
        PsiElement next = nextSignificantLeaf(element);
        return next != null && text.equals(next.getText());
    }

    private static boolean hasPreviousText(PsiElement element, String text) {
        PsiElement previous = previousSignificantLeaf(element);
        return previous != null && text.equals(previous.getText());
    }

    private static PsiElement nextSignificantLeaf(PsiElement element) {
        PsiElement current = PsiTreeUtil.nextLeaf(element);
        while (current instanceof PsiWhiteSpace || current instanceof PsiComment) {
            current = PsiTreeUtil.nextLeaf(current);
        }
        return current;
    }

    private static PsiElement previousSignificantLeaf(PsiElement element) {
        PsiElement current = PsiTreeUtil.prevLeaf(element);
        while (current instanceof PsiWhiteSpace || current instanceof PsiComment) {
            current = PsiTreeUtil.prevLeaf(current);
        }
        return current;
    }
}
